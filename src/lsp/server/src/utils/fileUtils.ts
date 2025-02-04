import { promises as fs } from "fs";
import * as os from "os";
import path = require("path");
class FileUtils {
  private static instance: FileUtils;

  private constructor() {}

  public static getInstance(): FileUtils {
    if (!FileUtils.instance) {
      FileUtils.instance = new FileUtils();
    }
    return FileUtils.instance;
  }

  public async readFile(filePath: string): Promise<string> {
    try {
      const data = await fs.readFile(filePath, "utf8");
      return data;
    } catch (err) {
      console.error(`Error reading file from path: ${filePath}`, err);
      throw err;
    }
  }

  public async writeFile(filePath: string, data: string): Promise<void> {
    try {
      // Ensure the directory exists
      const dir = path.dirname(filePath);
      await fs.mkdir(dir, { recursive: true });

      await fs.writeFile(filePath, data, "utf8");
    } catch (err) {
      console.error(`Error writing file to path: ${filePath}`, err);
      throw err;
    }
  }

  public async readJsonFile<T>(filePath: string): Promise<T> {
    try {
      const data = await this.readFile(filePath);
      return JSON.parse(data) as T;
    } catch (err) {
      console.error(`Error parsing JSON from file: ${filePath}`, err);
      throw err;
    }
  }

  public async doesFileExist(filePath: string): Promise<boolean> {
    try {
      await fs.access(filePath);
      return true;
    } catch (err) {
      console.log("File does not exist yet", err);
      return false;
    }
  }

  public async createTempFile({
    fileName,
    data = "",
  }: {
    fileName: string;
    data?: string;
  }): Promise<string> {
    const tempDir = os.tmpdir();
    const filePath = path.join(tempDir, fileName);
    await this.writeFile(filePath, data);

    return filePath;
  }

  public getTempFilePath({ fileName }: { fileName: string }): string {
    const tempDir = os.tmpdir();
    const filePath = path.join(tempDir, fileName);
    return filePath;
  }

  public async findFileBreadthFirst(startDir: string, targetFileName: string) {
    const queue = [startDir];

    while (queue.length > 0) {
      const currentDir = queue.shift();
      const filesAndDirs = await fs.readdir(currentDir);

      for (const item of filesAndDirs) {
        const fullPath = path.join(currentDir, item);
        const stat = await fs.stat(fullPath);

        if (stat.isFile() && item === targetFileName) {
          return fullPath;
        }

        if (stat.isDirectory()) {
          queue.push(fullPath);
        }
      }
    }

    return null; // If the file is not found
  }

  async bfsTraverseVisit(
    rootFolder: string,
    callBack: (uri: string) => void
  ): Promise<void> {
    const queue: string[] = [rootFolder];

    while (queue.length > 0) {
      const currentPath = queue.shift();
      const filesAndDirs = await fs.readdir(currentPath);

      for (const item of filesAndDirs) {
        const fullPath = path.join(currentPath, item);

        if ((await fs.stat(fullPath)).isDirectory()) {
          queue.push(fullPath);
        } else if (
          (await fs.stat(fullPath)).isFile() &&
          path.extname(fullPath) === ".fg"
        ) {
          callBack(fullPath);
        }
      }
    }
  }
}

export const fileUtils = FileUtils.getInstance();
