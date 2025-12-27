import os
import re
import pathlib

def extract_string_literal(content):
    """
    Extracts string content from C++ string literal (raw or normal).
    Returns the content and the matched length.
    """
    # Raw string: R"(...)" or R"delimiter(...)delimiter"
    # Simplified raw string regex for R"(...)"
    raw_match = re.match(r'R"\((.*?)\)"', content, re.DOTALL)
    if raw_match:
        return raw_match.group(1), raw_match.end()
    
    # Normal string: "..."
    if content.startswith('"'):
        end = 1
        escaped = False
        result = ""
        while end < len(content):
            char = content[end]
            if escaped:
                if char == 'n': result += '\n'
                elif char == 't': result += '\t'
                elif char == 'r': result += '\r'
                elif char == '\\': result += '\\'
                elif char == '"': result += '"'
                else: result += '\\' + char 
                escaped = False
            elif char == '\\':
                escaped = True
            elif char == '"':
                return result, end + 1
            else:
                result += char
            end += 1
    return None, 0

def find_test_blocks(content):
    regex = re.compile(r'TEST_F\s*\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*\{')
    pos = 0
    while True:
        match = regex.search(content, pos)
        if not match: break
        
        # Check if commented out
        line_start = content.rfind('\n', 0, match.start()) + 1
        line_prefix = content[line_start:match.start()].strip()
        if line_prefix.startswith('//'):
            pos = match.end()
            continue

        start_idx = match.end() - 1
        
        # Robust brace counting
        open_braces = 0
        i = start_idx
        length = len(content)
        in_string = False
        string_char = None
        in_raw_string = False
        in_comment = False 
        in_block_comment = False 
        
        found_body = False
        end_idx = -1
        
        while i < length:
            c = content[i]
            
            if in_comment:
                if c == '\n': in_comment = False
            elif in_block_comment:
                if c == '*' and i+1 < length and content[i+1] == '/':
                    in_block_comment = False
                    i += 1
            elif in_raw_string:
                # Naive: look for )" - assumes no custom delimiters
                if c == ')' and i+1 < length and content[i+1] == '"':
                     in_raw_string = False
                     i += 1
            elif in_string:
                if c == '\\': i += 1 
                elif c == string_char: in_string = False
            else:
                if c == '/' and i+1 < length and content[i+1] == '/':
                    in_comment = True
                    i += 1
                elif c == '/' and i+1 < length and content[i+1] == '*':
                    in_block_comment = True
                    i += 1
                elif c == 'R' and i+2 < length and content[i+1] == '"' and content[i+2] == '(':
                    in_raw_string = True
                    i += 2
                elif c == '"' or c == "'":
                    in_string = True
                    string_char = c
                elif c == '{':
                    open_braces += 1
                elif c == '}':
                    open_braces -= 1
                    if open_braces == 0:
                        end_idx = i + 1
                        found_body = True
                        break
            i += 1
            
        if found_body:
            yield match.group(1), match.group(2), content[start_idx+1:end_idx-1]
            pos = end_idx
        else:
            print(f"Warning: Could not find end of block for {match.group(1)}.{match.group(2)}")
            pos = match.end()

def parse_simple_input_output(body):
    input_code = None
    expected_output = None
    
    # Try finding I(...) or IE(...) first
    i_match = re.search(r'\b(?:I|IE)\s*\(\s*', body)
    if i_match:
        remaining = body[i_match.end():]
        extracted, length = extract_string_literal(remaining)
        if extracted is not None:
            input_code = extracted
            
    if not input_code:
        input_match = re.search(r'std::string\s+input\s*=\s*', body)
        if input_match:
            remaining = body[input_match.end():]
            extracted, length = extract_string_literal(remaining)
            if extracted is not None:
                input_code = extracted
                
    if not input_code:
        set_input_match = re.search(r'setInput\s*\(\s*', body)
        if set_input_match:
             remaining = body[set_input_match.end():]
             extracted, length = extract_string_literal(remaining)
             if extracted is not None:
                 input_code = extracted

    expect_eq_match = re.search(r'EXPECT_EQ\s*\(\s*getOutput\(\)\s*,\s*', body)
    if expect_eq_match:
        remaining = body[expect_eq_match.end():]
        extracted, length = extract_string_literal(remaining)
        if extracted is not None:
            expected_output = extracted
            
    if not expected_output:
        var_match = re.search(r'std::string\s+expected_output\s*=\s*', body)
        if var_match:
            remaining = body[var_match.end():]
            extracted, length = extract_string_literal(remaining)
            if extracted is not None:
                expected_output = extracted

    if not expected_output:
        var_match = re.search(r'expected_output\s*=\s*', body)
        if var_match:
            remaining = body[var_match.end():]
            extracted, length = extract_string_literal(remaining)
            if extracted is not None:
                expected_output = extracted
                
    return input_code, expected_output

def parse_body_advanced(body):
    error_match = re.search(r'EXPECT_ERROR_CODE\s*\(\s*(?:[\w:]*::)*(\w+)\s*\)', body)
    error_code = error_match.group(1) if error_match else None
    
    # Check for writeFile (multi-file) first
    write_file_matches = list(re.finditer(r'writeFile\s*\(\s*"(.*?)"\s*,\s*', body))
    if write_file_matches:
        files = []
        for match in write_file_matches:
            filename = match.group(1)
            remaining = body[match.end():]
            content, _ = extract_string_literal(remaining)
            if content is not None:
                files.append((filename, content))
        
        target_match = re.search(r'createBuildAndRunCmd\s*\(\s*"(.*?)"\s*\)', body)
        target = target_match.group(1) if target_match else None
        
        _, expected_output = parse_simple_input_output(body)
        
        return {
            'type': 'multi',
            'files': files,
            'target': target,
            'expected': expected_output,
            'error_code': error_code
        }

    if error_code:
        input_code, _ = parse_simple_input_output(body)
        return {
            'type': 'diagnostic',
            'error_code': error_code,
            'input': input_code
        }

    # Default simple case
    input_code, expected_output = parse_simple_input_output(body)
    if input_code:
        return {
            'type': 'simple',
            'input': input_code,
            'expected': expected_output
        }
    
    return None

def main():
    source_dir = pathlib.Path("tests-type")
    target_dir = pathlib.Path("fixtures")
    
    files = list(source_dir.rglob("*.cpp"))
    
    count = 0
    skipped = 0
    
    for file_path in files:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            
        rel_path = file_path.relative_to(source_dir).parent
        
        for suite, name, body in find_test_blocks(content):
            result = parse_body_advanced(body)
            
            if result:
                output_subdir = target_dir / rel_path / file_path.stem
                if result['type'] == 'multi':
                    output_subdir = output_subdir / name
                
                output_subdir.mkdir(parents=True, exist_ok=True)
                
                if result['type'] == 'simple':
                    fg_path = output_subdir / f"{name}.fg"
                    expect_path = output_subdir / f"{name}.expect"
                    
                    with open(fg_path, 'w', encoding='utf-8') as f:
                        f.write(result['input'].strip() + "\n")
                    
                    with open(expect_path, 'w', encoding='utf-8') as f:
                        f.write(result['expected'] if result['expected'] is not None else "")
                            
                elif result['type'] == 'diagnostic':
                    if result['input']:
                        fg_path = output_subdir / f"{name}.fg"
                        content = f"/; EXPECT_ERROR: {result['error_code']}\n" + result['input'].strip() + "\n"
                        with open(fg_path, 'w', encoding='utf-8') as f:
                            f.write(content)
                    else:
                        print(f"Skipping {file_path.name}::{name} - Diagnostic test missing input")
                        skipped += 1
                        
                elif result['type'] == 'multi':
                    for filename, content in result['files']:
                        file_path_out = output_subdir / filename
                        # Check if this is the target file and if we have error code
                        if result['error_code'] and result['target'] and filename == result['target']:
                             content = f"/; EXPECT_ERROR: {result['error_code']}\n" + content
                        
                        with open(file_path_out, 'w', encoding='utf-8') as f:
                            f.write(content)
                            
                    if result['target'] and result['expected'] is not None and not result['error_code']:
                         # Only write expect if not diagnostic
                         target_path = output_subdir / result['target']
                         expect_path = target_path.with_suffix(".expect")
                         with open(expect_path, 'w', encoding='utf-8') as f:
                             f.write(result['expected'])
                    
                count += 1
            else:
                print(f"Skipping {file_path.name}::{suite}::{name} - No recognized pattern")
                skipped += 1

    print(f"Migrated {count} tests. Skipped {skipped} blocks.")

if __name__ == "__main__":
    main()
