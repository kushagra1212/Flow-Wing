import os, re

OUTPUT_FILE = "codebase_dump.txt"
INCLUDE_DIRS = ['src/syntax', 'src/ASTBuilder', 'src/ASTVisitor', 'src/SemanticAnalyzer', 'src/IRGen']
ALLOWED_EXTENSIONS = {'.cpp', '.h', '.hpp'}
IGNORE_FILES = {OUTPUT_FILE, 'code_dump.py'}

def get_file_list():
    """Scans directories and returns a list of valid file paths."""
    valid_files = []
    
    # Process root if needed (optional)
    # for f in os.listdir('.'): ... 

    for d in INCLUDE_DIRS:
        if os.path.exists(d):
            for root, _, files in os.walk(d):
                for f in files:
                    if f in IGNORE_FILES: continue
                    ext = os.path.splitext(f)[1].lower()
                    if ext in ALLOWED_EXTENSIONS:
                        valid_files.append(os.path.join(root, f))
    return valid_files

def get_tree_structure(file_list):
    """Creates a visual string representation of the file tree."""
    tree = ["# PROJECT STRUCTURE"]
    for path in sorted(file_list):
        tree.append(f"#  - {path}")
    return "\n".join(tree) + "\n\n"

def clean_code(text):
    """Removes comments and excess whitespace."""
    # Remove // and /* */ comments
    text = re.sub(r'//.*|/\*[\s\S]*?\*/', '', text)
    # Collapse multiple empty lines into one
    return re.sub(r'\n\s*\n', '\n', text).strip()

def create_smart_dump():
    all_files = get_file_list()
    
    # HEURISTIC: Sort files by importance
    # 1. Headers (.h, .hpp) - The "What" (Definitions/API) - AI needs this first
    # 2. Source (.cpp) - The "How" (Implementation)
    headers = sorted([f for f in all_files if f.endswith(('.h', '.hpp'))])
    sources = sorted([f for f in all_files if f.endswith('.cpp')])
    
    ordered_files = headers + sources

    with open(OUTPUT_FILE, "w", encoding="utf-8") as out:
        # 1. Write the Tree Map (High-level analysis)
        out.write(get_tree_structure(ordered_files))
        
        # 2. Write the content
        for path in ordered_files:
            try:
                with open(path, 'r', encoding='utf-8') as f:
                    content = clean_code(f.read())
                    
                    print(f"Adding: {path}")
                    out.write(f"{'='*30}\n")
                    out.write(f"FILE: {path}\n")
                    out.write(f"{'='*30}\n")
                    out.write(content + "\n\n")
            except Exception as e:
                print(f"Skipping {path}: {e}")

    print(f"Done! Analyzed {len(ordered_files)} files. Saved to: {OUTPUT_FILE}")

if __name__ == "__main__":
    create_smart_dump()