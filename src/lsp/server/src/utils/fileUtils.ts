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
}

export const fileUtils = FileUtils.getInstance();
