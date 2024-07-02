import { promises as fs } from "fs";

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
}

export const fileUtils = FileUtils.getInstance();
