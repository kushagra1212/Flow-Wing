# Scope Aware JSON for LSP

e.g

```fg
var x = 42;
{
    var x = 10;
    x + 2
}
```

```json
{
  "scopes": [
    {
      "id": 0,
      "type": "global",
      "range": { "start": 0, "end": 40 },
      "parent": null,
      "symbols": [
        {
          "name": "x",
          "type": "Int",
          "range": { "start": 4, "end": 5 },
          "definitionRange": { "start": 0, "end": 11 }
        }
      ]
    },
    {
      "id": 1,
      "type": "block",
      "range": { "start": 12, "end": 38 },
      "parent": 0,
      "symbols": [
        {
          "name": "x",
          "type": "Int",
          "range": { "start": 18, "end": 19 },
          "definitionRange": { "start": 12, "end": 22 }
        }
      ]
    }
  ]
}
```

Semantic Output:

```json
{
  "semantic": {
    "scopes": [...],
    "symbols": [...],     // (optional flattened list)
    "types": {...},       // type info for expressions
    "references": [...],  // where each symbol is used
    "errors": [...]
  }
}

```
