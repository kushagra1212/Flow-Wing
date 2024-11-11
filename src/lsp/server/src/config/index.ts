import { getModulePath } from "../utils";

class FlowWingConfig {
  private _flowWingPath: string;
  private _modulePath: string = getModulePath();
  private readonly _syntaxFileExt = ".json";
  private readonly _tokenFileExt = ".tokens.json";
  private readonly _errorFileExt = ".err.json";
  private _doesFlowWingExist: boolean = false;

  constructor(flowWingPath: string) {
    this._flowWingPath = flowWingPath;
  }

  get flowWingPath(): string {
    return this._flowWingPath;
  }

  set flowWingPath(newPath: string) {
    this._flowWingPath = newPath;
  }

  get modulePath(): string {
    return this._modulePath;
  }

  set modulePath(newPath: string) {
    this._modulePath = newPath;
  }

  get doesFlowWingExist(): boolean {
    return this._doesFlowWingExist;
  }

  set doesFlowWingExist(exists: boolean) {
    this._doesFlowWingExist = exists;
  }

  get temp() {
    return {
      syntaxFileExt: this._syntaxFileExt,
      tokenFileExt: this._tokenFileExt,
      errorFileExt: this._errorFileExt,
    };
  }
}

const flowWingConfig = new FlowWingConfig("FlowWing");

export { flowWingConfig };
