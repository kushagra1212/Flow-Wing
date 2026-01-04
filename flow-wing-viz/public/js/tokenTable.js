export class TokenTable {
  constructor(containerId, onRowHover) {
    this.container = document.getElementById(containerId);
    this.onRowHover = onRowHover;
  }

  render(tokens) {
    this.container.innerHTML = "";

    const wrapper = document.createElement("div");
    wrapper.className = "token-table-container";

    const table = document.createElement("table");
    table.className = "token-table";

    // Header
    const thead = document.createElement("thead");
    thead.innerHTML = `
            <tr>
                <th style="width: 80px">Ln:Col</th>
                <th style="width: 150px">Type</th>
                <th>Lexeme</th>
            </tr>
        `;
    table.appendChild(thead);

    // Body
    const tbody = document.createElement("tbody");

    tokens.forEach((token) => {
      const tr = document.createElement("tr");

      // Location
      const loc = `${token.range.start[0]}:${token.range.start[1]}`;

      // Format lexeme (handle newlines specially for display)
      let displayLexeme = token.lexeme || "";
      if (displayLexeme === "\n") displayLexeme = "\\n";
      if (displayLexeme === "\r") displayLexeme = "\\r";
      if (displayLexeme === "\t") displayLexeme = "\\t";

      // Create cells with proper text escaping
      const locCell = document.createElement("td");
      locCell.textContent = loc;
      locCell.style.color = "var(--text-dim)";

      const typeCell = document.createElement("td");
      const typePill = document.createElement("span");
      typePill.className = "type-pill";
      typePill.textContent = token.type;
      typeCell.appendChild(typePill);

      const lexemeCell = document.createElement("td");
      lexemeCell.className = "lexeme-cell";
      lexemeCell.textContent = displayLexeme;

      tr.appendChild(locCell);
      tr.appendChild(typeCell);
      tr.appendChild(lexemeCell);

      // Hover Interaction
      tr.onmouseenter = () => {
        // Highlight row
        this.container
          .querySelectorAll("tr")
          .forEach((r) => r.classList.remove("active-row"));
        tr.classList.add("active-row");
        // Tell App to highlight code
        this.onRowHover(token);
      };

      tbody.appendChild(tr);
    });

    table.appendChild(tbody);
    wrapper.appendChild(table);
    this.container.appendChild(wrapper);
  }
}
