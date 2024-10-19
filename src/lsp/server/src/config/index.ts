const FILE_NAME = "fgcode";

type FlowWingConfig = {
  compiler: {
    flowWingPath: string;
  };
  temp: {
    syntaxFileExt: ".json";
    tokenFileExt: ".tokens.json";
    errorFileExt: ".err.json";
  };
};

export const flowWingConfig: FlowWingConfig = {
  compiler: {
    flowWingPath:
      "/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing",
  },
  temp: {
    syntaxFileExt: ".json",
    tokenFileExt: ".tokens.json",
    errorFileExt: ".err.json",
  },
};
