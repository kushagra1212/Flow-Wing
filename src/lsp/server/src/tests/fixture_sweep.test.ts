import { assert } from "chai";
import * as path from "path";
import * as fs from "fs";
import { flowWingConfig } from "../config";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSemPathForDocument } from "../services/documentService";
import { 
  getHoverFromSem, 
  getSymbolAtPosition, 
  isSemFormat 
} from "../services/semService";
import { fileUtils } from "../utils/fileUtils";
import { getTestCompilerPath, getTestFixturesDir, pathToFileUri } from "./testCompilerPath";

describe("Systematic Fixture Sweep (LatestTests)", () => {
    const compilerPath = getTestCompilerPath();
    const fixturesDir = getTestFixturesDir();

    before(async () => {
        flowWingConfig.flowWingPath = compilerPath;
    });

    const categories = [
        "01_basics",
        "01_bool",
        "01_char",
        "01_conversion",
        "01_deci",
        "01_int",
        "01_string",
        "01_unary",
        "ArrayTests",
        "BinaryOperationLiteralTests",
        "ConditionalTests",
        "ConstTests",
        "ConstVariableDeclarationTests",
        "ContainerTests",
        "DynamicTests",
        "DynamicVariableTests",
        "EdgeCaseTests",
        "FunctionTests",
        "IndexTests",
        "MixtureTests",
        "ObjectTests/declaration",
        "PrimitiveTests",
        "ScopeTests",
        "TypeConversionFunctionTests",
        "UnaryOperationLiteralTests",
        "VariableDeclarationTests",
        "arrays"
    ];

    function getFilesRecursive(dir: string): string[] {
        let results: string[] = [];
        const list = fs.readdirSync(dir);
        list.forEach(file => {
            file = path.join(dir, file);
            const stat = fs.statSync(file);
            if (stat && stat.isDirectory()) {
                results = results.concat(getFilesRecursive(file));
            } else if (file.endsWith(".fg")) {
                results.push(file);
            }
        });
        return results;
    }

    async function runFixtureCheck(filePath: string, dir: string): Promise<{ relativePath: string; error?: string }> {
        const relativePath = path.relative(dir, filePath);
        try {
            const content = fs.readFileSync(filePath, "utf-8");
            const document = TextDocument.create(pathToFileUri(filePath), "flowwing", 0, content);

            const semPath = await getSemPathForDocument(document, { position: { line: 0, character: 0 } });
            const isErrorFile = relativePath.includes("error") || content.includes("EXPECT_ERROR");

            if (!isErrorFile) {
                assert.isNotNull(semPath, `SEM path should not be null for ${relativePath}`);
            }

            if (semPath) {
                const semContent = await fileUtils.readFile(semPath!);
                const semJson = JSON.parse(semContent);
                assert.isTrue(isSemFormat(semJson), `Should be valid SEM format for ${relativePath}`);

                const lines = content.split("\n");
                let resolvedCount = 0;
                for (let l = 0; l < Math.min(lines.length, 20); l++) {
                    const words = lines[l].matchAll(/\b[a-zA-Z_][a-zA-Z0-9_]*\b/g);
                    for (const match of words) {
                        if (["fun", "var", "const", "type", "return", "if", "else", "while", "for", "println", "print", "nthg", "i32", "i64", "int", "f32", "f64", "deci", "str", "bool", "char"].includes(match[0])) continue;

                        const pos = { line: l, character: match.index! + 1 };
                        const result = getSymbolAtPosition(semJson, pos, match[0]);
                        if (result) {
                            resolvedCount++;
                            const hover = getHoverFromSem(semJson, pos, match[0]);
                            assert.isNotNull(hover, `Hover should be available for ${match[0]} in ${relativePath}`);
                            break;
                        }
                    }
                    if (resolvedCount > 0) break;
                }
            }
            return { relativePath };
        } catch (err) {
            return { relativePath, error: String(err) };
        }
    }

    for (const category of categories) {
        describe(`Category: ${category}`, () => {
            const dir = path.join(fixturesDir, category);
            if (!fs.existsSync(dir)) return;

            const allFiles = getFilesRecursive(dir);

            it(`should generate valid LSP data for all ${allFiles.length} files (parallel)`, async function () {
                this.timeout(60000); // 60s for parallel batch
                const results = await Promise.all(
                    allFiles.map((filePath) => runFixtureCheck(filePath, dir))
                );
                const failures = results.filter((r) => r.error);
                if (failures.length > 0) {
                    assert.fail(
                        `Failed for ${failures.length} file(s):\n` +
                        failures.map((f) => `  ${f.relativePath}: ${f.error}`).join("\n")
                    );
                }
            });
        });
    }
});
