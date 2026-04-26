Prism.languages.flowwing = {
  comment: {
    // Single line comments
    pattern: /\/;.*/,
    greedy: true,
  },
  "block-comment": {
    pattern: /\/#[\s\S]*?#\//,
    greedy: true,
  },
  // Keywords

  // Control flow and logical operators
  operator: [
    /->/, // skinny arrow
    /(?:\^|\||\|\||&&|<<|>>|!)(?!=)/, // logical operators
    /([+%]|(\*(?!\w))|-(?!>)|\/(?!\/))/,
    /((?<![<>])=(?!=|>))/,
    /(>=|<=|!=|==)/, // comparison operators
    /[<>]/,
  ],

  // Constants
  constant: /\b(?:true|false|null)\b/,

  // Functions
  function: {
    pattern: /\b[a-zA-Z_][a-zA-Z0-9_]*\s*(?=\()/,
    greedy: true,
  },

  // Variables
  variable: /\b(?<!\.\.)(?:r#(?!(self|super)))?[a-z0-9_]+\b/,

  // Attributes
  "meta.attribute": {
    pattern: /(#)(!?)(\[)[\s\S]*?\]/,
    lookbehind: true,
    inside: {
      punctuation: /[{}[\]]/,
    },
  },

  // Strings
  string: {
    pattern: /(["'])(?:(?!\1)[^\\]|\\.)*\1/,
    greedy: true,
  },

  // Numbers
  number: {
    pattern: RegExp(
      /(^|[^\w$])/.source +
        "(?:" +
        // constant
        (/NaN|Infinity/.source +
          "|" +
          // binary integer
          /0[bB][01]+(?:_[01]+)*n?/.source +
          "|" +
          // octal integer
          /0[oO][0-7]+(?:_[0-7]+)*n?/.source +
          "|" +
          // hexadecimal integer
          /0[xX][\dA-Fa-f]+(?:_[\dA-Fa-f]+)*n?/.source +
          "|" +
          // decimal bigint
          /\d+(?:_\d+)*n/.source +
          "|" +
          // decimal number (integer or float) but no bigint
          /(?:\d+(?:_\d+)*(?:\.(?:\d+(?:_\d+)*)?)?|\.\d+(?:_\d+)*)(?:[Ee][+-]?\d+(?:_\d+)*)?/
            .source) +
        ")" +
        /(?![\w$])/.source
    ),
    lookbehind: true,
  },

  // Punctuation
  punctuation: /[.,;{}()\[\]]/,
};

Prism.languages.flowwing = {
  comment: [
    {
      pattern: /(^|[^\\])\/#[\s\S]*?(?:#\/|$)/,
      lookbehind: true,
      greedy: true,
    },
    {
      pattern: /(^|[^\\:])\/\;.*/,
      lookbehind: true,
      greedy: true,
    },
  ],
  string: {
    pattern: /(["'])(?:\\(?:\r\n|[\s\S])|(?!\1)[^\\\r\n])*\1/,
    greedy: true,
  },
  "class-name": {
    pattern: /(\b(?:class|extends|new)\s+|\bcatch\s+\()[\w.\\]+/i,
    lookbehind: true,
    inside: {
      punctuation: /[.\\]/,
    },
  },
  keyword:
    /\b(?:break|continue|else|for|if|or if|return|switch|case|while|expose|default|var|const|type|fun|inout|as|self|Nir|bring|from|extends|decl|fill|new|module|init|class|(?:int|deci32|str|bool|nthg|deci))\b/,

  boolean: /\b(?:false|true)\b/,
  function: /\b\w+(?=\()/,
  number: /\b0x[\da-f]+\b|(?:\b\d+(?:\.\d*)?|\B\.\d+)(?:e[+-]?\d+)?/i,
  operator: /[<>]=?|[!=]=?=?|--?|\+\+?|&&?|\|\|?|[?*/~^%]/,
  punctuation: /[{}[\];(),.:]/,
};
