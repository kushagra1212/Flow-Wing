const FILE_NAME = "fgcode";

type FlowWingConfig = {
  compiler: {
    flowWingPath: string;
  };
  temp: {
    codeFileName: string;
    syntaxFileName: string;
    tokenFileName: string;
    errorFileName: string;
  };
};

export const flowWingConfig: FlowWingConfig = {
  compiler: {
    flowWingPath:
      "/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing",
  },
  temp: {
    codeFileName: FILE_NAME + ".fg",
    syntaxFileName: FILE_NAME + ".json",
    tokenFileName: FILE_NAME + ".tokens.json",
    errorFileName: FILE_NAME + ".err.json",
  },
};
