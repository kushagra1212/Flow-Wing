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
    flowWingPath: "FlowWing",
  },
  temp: {
    syntaxFileExt: ".json",
    tokenFileExt: ".tokens.json",
    errorFileExt: ".err.json",
  },
};
