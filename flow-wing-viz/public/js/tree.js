export class TreeVisualizer {
  constructor(containerId, onNodeHover) {
    this.containerId = containerId;
    this.container = document.getElementById(containerId);
    this.onNodeHover = onNodeHover;
    this.root = null;
    this.zoom = null;
    this.svg = null;
    this.g = null;
    this.lastData = null;
    this.semanticData = null;
    this.isSemanticView = false;
    this.resizeObserver = null;

    // Handle container resize
    if (window.ResizeObserver) {
      this.resizeObserver = new ResizeObserver(() => {
        // Only re-render if we're actually displaying tree data (not LLVM IR or other views)
        if (this.lastData && this.container && this.container.querySelector("svg")) {
          this.render(this.lastData);
        }
      });
      this.resizeObserver.observe(this.container);
    }
  }

  setSemanticData(semData) {
    this.semanticData = semData;
  }

  render(data) {
    this.lastData = data;
    this.container.innerHTML = "";

    if (!data) {
      this.container.innerHTML =
        '<div style="padding: 20px; color: #8b949e; text-align: center;">No tree data available</div>';
      return;
    }

    // Check if this is semantic view
    this.isSemanticView = this.semanticData !== null;

    const width = this.container.clientWidth || 800;
    const height = this.container.clientHeight || 600;

    const hierarchyData = this.transformToHierarchy(data);
    if (!hierarchyData) {
      this.container.innerHTML =
        '<div style="padding: 20px; color: #8b949e; text-align: center;">Failed to parse tree data</div>';
      return;
    }

    const root = d3.hierarchy(hierarchyData);

    // Calculate tree dimensions with better spacing
    const nodeHeight = 80; // Increased vertical spacing
    const nodeWidth = 200; // Increased horizontal spacing
    const treeLayout = d3.tree().nodeSize([nodeHeight, nodeWidth]);
    treeLayout(root);

    // Check if we have any nodes
    if (!root || root.descendants().length === 0) {
      this.container.innerHTML =
        '<div style="padding: 20px; color: #8b949e; text-align: center;">No tree data available</div>';
      return;
    }

    // Calculate bounds for centering
    let x0 = Infinity;
    let x1 = -Infinity;
    let y0 = Infinity;
    let y1 = -Infinity;

    root.each((d) => {
      if (d.x > x1) x1 = d.x;
      if (d.x < x0) x0 = d.x;
      if (d.y > y1) y1 = d.y;
      if (d.y < y0) y0 = d.y;
    });

    const dx = x1 - x0 + nodeHeight * 2;
    const dy = y1 - y0 + nodeWidth * 2;

    // Create SVG with zoom
    this.svg = d3
      .select(`#${this.containerId}`)
      .append("svg")
      .attr("width", width)
      .attr("height", height)
      .style("background", "#0d1117");

    // Create zoom behavior
    this.zoom = d3
      .zoom()
      .scaleExtent([0.1, 3])
      .on("zoom", (e) => {
        this.g.attr("transform", e.transform);
      });

    this.svg.call(this.zoom);

    // Calculate initial transform to center the tree
    const initialX = nodeWidth;
    const initialY = (height - dx) / 2 - x0;

    // Main group with initial transform
    this.g = this.svg
      .append("g")
      .attr("transform", `translate(${initialX},${initialY})`);

    // Links with gradient (using actual colors, not CSS variables)
    const defs = this.svg.append("defs");

    // Create gradients for different link types
    const treeGradient = defs
      .append("linearGradient")
      .attr("id", "link-gradient")
      .attr("gradientUnits", "userSpaceOnUse")
      .attr("x1", 0)
      .attr("y1", 0)
      .attr("x2", 0)
      .attr("y2", 1);

    treeGradient
      .append("stop")
      .attr("offset", "0%")
      .attr("stop-color", "#58a6ff")
      .attr("stop-opacity", 0.6);

    treeGradient
      .append("stop")
      .attr("offset", "100%")
      .attr("stop-color", "#58a6ff")
      .attr("stop-opacity", 0.2);

    // Type link gradient (for semantic tree)
    const typeGradient = defs
      .append("linearGradient")
      .attr("id", "type-link-gradient")
      .attr("gradientUnits", "userSpaceOnUse")
      .attr("x1", 0)
      .attr("y1", 0)
      .attr("x2", 0)
      .attr("y2", 1);

    typeGradient
      .append("stop")
      .attr("offset", "0%")
      .attr("stop-color", "#ff7b72")
      .attr("stop-opacity", 0.8);

    typeGradient
      .append("stop")
      .attr("offset", "100%")
      .attr("stop-color", "#ff7b72")
      .attr("stop-opacity", 0.3);

    // Symbol link gradient (for semantic tree)
    const symbolGradient = defs
      .append("linearGradient")
      .attr("id", "symbol-link-gradient")
      .attr("gradientUnits", "userSpaceOnUse")
      .attr("x1", 0)
      .attr("y1", 0)
      .attr("x2", 0)
      .attr("y2", 1);

    symbolGradient
      .append("stop")
      .attr("offset", "0%")
      .attr("stop-color", "#79c0ff")
      .attr("stop-opacity", 0.8);

    symbolGradient
      .append("stop")
      .attr("offset", "100%")
      .attr("stop-color", "#79c0ff")
      .attr("stop-opacity", 0.3);

    // Tree structure links
    const link = this.g
      .selectAll(".link")
      .data(root.links())
      .enter()
      .append("path")
      .attr("class", "link tree-link")
      .attr("fill", "none")
      .attr("stroke", "#58a6ff")
      .attr("stroke-width", 2)
      .attr("opacity", 0.6)
      .attr(
        "d",
        d3
          .linkHorizontal()
          .x((d) => d.y)
          .y((d) => d.x)
      );

    // Nodes (draw before semantic links so semantic links appear on top)
    const node = this.g
      .selectAll(".node")
      .data(root.descendants())
      .enter()
      .append("g")
      .attr("class", "node")
      .attr("transform", (d) => `translate(${d.y},${d.x})`)
      .style("cursor", "pointer")
      .style("opacity", 1);

    // Add semantic links if in semantic view (draw after nodes so they appear on top)
    if (this.isSemanticView && this.semanticData) {
      this.renderSemanticLinks(root, defs);
    }

    // Node circles with better styling - different colors for type_id vs symbol_id
    node
      .append("circle")
      .attr("r", (d) => (d.children ? 8 : 6))
      .attr("fill", (d) => {
        // In semantic view, check for type_id or symbol_id (handle both camelCase and snake_case)
        if (this.isSemanticView && d.data.raw) {
          const raw = d.data.raw;
          const typeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
          const symbolId =
            raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
          // Priority: type_id > symbol_id > default
          if (typeId !== undefined && typeId !== null) {
            return "#ff7b72"; // Type color (red)
          }
          if (symbolId !== undefined && symbolId !== null) {
            return "#79c0ff"; // Symbol color (blue)
          }
        }
        // Default colors based on children
        if (d.children) {
          return "#58a6ff"; // accent color
        }
        return "#d2a8ff"; // sh-func color
      })
      .attr("stroke", "#fff")
      .attr("stroke-width", 2)
      .attr("filter", "drop-shadow(0 2px 4px rgba(0,0,0,0.3))");

    // Node labels with background
    const labelGroup = node.append("g").attr("class", "node-label");

    // Helper function to get full label text
    const getLabelText = (d) => {
      let name = d.data.name;

      // Add semantic info to labels in semantic view (handle both camelCase and snake_case)
      if (this.isSemanticView && d.data.raw) {
        const raw = d.data.raw;
        const typeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
        const symbolId =
          raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
        if (
          typeId !== undefined &&
          typeId !== null &&
          this.semanticData.types &&
          this.semanticData.types[typeId]
        ) {
          const typeName = this.semanticData.types[typeId].name || `T${typeId}`;
          name += ` [T:${
            typeName.length > 8 ? typeName.substring(0, 8) + "..." : typeName
          }]`;
        }
        if (
          symbolId !== undefined &&
          symbolId !== null &&
          this.semanticData.symbols &&
          this.semanticData.symbols[symbolId]
        ) {
          const symbolName =
            this.semanticData.symbols[symbolId].name || `S${symbolId}`;
          name += ` [S:${
            symbolName.length > 8
              ? symbolName.substring(0, 8) + "..."
              : symbolName
          }]`;
        }
      }

      return name;
    };

    // Helper function to truncate text
    const truncateText = (text, maxLength = 40) => {
      if (text.length <= maxLength) return text;
      return text.substring(0, maxLength - 3) + "...";
    };

    labelGroup
      .append("rect")
      .attr("x", (d) => (d.children ? -90 : 12))
      .attr("y", -14)
      .attr("width", (d) => {
        const fullText = getLabelText(d);
        const textWidth = Math.min(fullText.length * 6.5, 180); // Cap at 180px
        return Math.max(textWidth + 16, 80);
      })
      .attr("height", 28)
      .attr("rx", 14)
      .attr("fill", (d) => {
        // In semantic view, match circle colors (handle both camelCase and snake_case)
        if (this.isSemanticView && d.data.raw) {
          const raw = d.data.raw;
          const typeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
          const symbolId =
            raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
          if (typeId !== undefined && typeId !== null) {
            return "rgba(255, 123, 114, 0.15)"; // Type color background
          }
          if (symbolId !== undefined && symbolId !== null) {
            return "rgba(121, 192, 255, 0.15)"; // Symbol color background
          }
        }
        // Default colors
        if (d.children) {
          return "rgba(88, 166, 255, 0.15)";
        }
        return "rgba(210, 168, 255, 0.15)";
      })
      .attr("stroke", (d) => {
        // In semantic view, match circle colors (handle both camelCase and snake_case)
        if (this.isSemanticView && d.data.raw) {
          const raw = d.data.raw;
          const typeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
          const symbolId =
            raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
          if (typeId !== undefined && typeId !== null) {
            return "#ff7b72"; // Type color border
          }
          if (symbolId !== undefined && symbolId !== null) {
            return "#79c0ff"; // Symbol color border
          }
        }
        // Default colors
        if (d.children) {
          return "#58a6ff"; // accent color
        }
        return "#d2a8ff"; // sh-func color
      })
      .attr("stroke-width", 1.5);

    // Main label text
    labelGroup
      .append("text")
      .attr("x", (d) => (d.children ? -50 : 20))
      .attr("y", 4)
      .attr("text-anchor", (d) => (d.children ? "end" : "start"))
      .attr("fill", "#c9d1d9") // text-main color
      .attr("font-size", "11px")
      .attr("font-weight", "500")
      .attr(
        "font-family",
        "-apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif"
      )
      .text((d) => {
        const fullText = getLabelText(d);
        return truncateText(fullText, 40);
      });

    // Hover interactions
    node
      .on("mouseover", (e, d) => {
        e.stopPropagation();
        // Call the hover callback with the raw node data
        if (d.data && d.data.raw) {
          this.onNodeHover(d.data.raw);
        } else {
          // Fallback: create a minimal node object
          this.onNodeHover({ kind: d.data.name, ...d.data });
        }

        d3.select(e.currentTarget).classed("active", true);

        // Highlight path to root
        const path = [];
        let current = d;
        while (current) {
          path.push(current);
          current = current.parent;
        }

        // Highlight nodes in path
        this.g
          .selectAll(".node")
          .classed("path-highlight", (n) => path.includes(n));

        // Highlight links in path
        this.g.selectAll(".link").classed("path-highlight", (l) => {
          return path.includes(l.source) && path.includes(l.target);
        });
      })
      .on("mouseout", (e) => {
        e.stopPropagation();
        d3.select(e.currentTarget).classed("active", false);
        this.g.selectAll(".node").classed("path-highlight", false);
        this.g.selectAll(".link").classed("path-highlight", false);
      });

    // Reset zoom to fit
    const scale = Math.min(
      1,
      (width - nodeWidth * 2) / (y1 - y0 + nodeWidth),
      (height - 40) / (x1 - x0 + nodeHeight)
    );
    const initialTransform = d3.zoomIdentity
      .translate(initialX, initialY)
      .scale(scale);
    this.svg.call(this.zoom.transform, initialTransform);
  }

  renderSemanticLinks(root, defs) {
    if (
      !this.semanticData ||
      !this.semanticData.types ||
      !this.semanticData.symbols
    )
      return;

    const nodes = root.descendants();
    const typeLinks = [];
    const symbolLinks = [];

    // Build a map of node positions by typeId and symbolId
    const nodesByTypeId = new Map();
    const nodesBySymbolId = new Map();
    const typeNodes = new Map();
    const symbolNodes = new Map();

    // First pass: collect all nodes with typeId/symbolId (don't create nodes yet)
    nodes.forEach((node) => {
      const raw = node.data.raw;
      if (!raw) return;

      // Track nodes with typeId (handle both camelCase and snake_case)
      const typeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
      if (typeId !== undefined && typeId !== null) {
        if (!nodesByTypeId.has(typeId)) {
          nodesByTypeId.set(typeId, []);
        }
        nodesByTypeId.get(typeId).push(node);
      }

      // Track typeIds arrays (handle both camelCase and snake_case)
      const typeIds = raw.typeIds || raw.type_ids;
      if (typeIds && Array.isArray(typeIds)) {
        typeIds.forEach((tid) => {
          if (!nodesByTypeId.has(tid)) {
            nodesByTypeId.set(tid, []);
          }
          nodesByTypeId.get(tid).push(node);
        });
      }

      // Track nodes with symbolId (handle both camelCase and snake_case)
      const symbolId =
        raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
      if (symbolId !== undefined && symbolId !== null) {
        if (!nodesBySymbolId.has(symbolId)) {
          nodesBySymbolId.set(symbolId, []);
        }
        nodesBySymbolId.get(symbolId).push(node);
      }

      // Track symbolIds arrays (handle both camelCase and snake_case)
      const symbolIds = raw.symbolIds || raw.symbol_ids;
      if (symbolIds && Array.isArray(symbolIds)) {
        symbolIds.forEach((sid) => {
          if (!nodesBySymbolId.has(sid)) {
            nodesBySymbolId.set(sid, []);
          }
          nodesBySymbolId.get(sid).push(node);
        });
      }
    });

    // Create type nodes at average positions of all nodes that share the type
    nodesByTypeId.forEach((nodesWithType, typeId) => {
      if (this.semanticData.types[typeId] && nodesWithType.length > 0) {
        const typeInfo = this.semanticData.types[typeId];
        // Calculate average position
        const avgX =
          nodesWithType.reduce((sum, n) => sum + n.x, 0) / nodesWithType.length;
        const avgY =
          nodesWithType.reduce((sum, n) => sum + n.y, 0) / nodesWithType.length;

        const typeNode = {
          id: `type-${typeId}`,
          typeId: typeId,
          name: typeInfo.name || typeId,
          kind: typeInfo.kind || "Type",
          x: avgX, // Average vertical position
          y: avgY, // Average horizontal position
          isType: true,
        };
        typeNodes.set(typeId, typeNode);
      }
    });

    // Create symbol nodes at average positions of all nodes that share the symbol
    nodesBySymbolId.forEach((nodesWithSymbol, symbolId) => {
      if (this.semanticData.symbols[symbolId] && nodesWithSymbol.length > 0) {
        const symbolInfo = this.semanticData.symbols[symbolId];
        // Calculate average position
        const avgX =
          nodesWithSymbol.reduce((sum, n) => sum + n.x, 0) /
          nodesWithSymbol.length;
        const avgY =
          nodesWithSymbol.reduce((sum, n) => sum + n.y, 0) /
          nodesWithSymbol.length;

        const symbolNode = {
          id: `symbol-${symbolId}`,
          symbolId: symbolId,
          name: symbolInfo.name || symbolId,
          kind: symbolInfo.kind || "Symbol",
          x: avgX, // Average vertical position
          y: avgY, // Average horizontal position
          isSymbol: true,
        };
        symbolNodes.set(symbolId, symbolNode);
      }
    });

    // Create type nodes visualization with collision avoidance
    // Group type nodes by y position to handle overlaps
    const typeNodesByY = new Map();
    typeNodes.forEach((typeNode, typeId) => {
      const yKey = Math.round(typeNode.y / 20) * 20; // Group by rounded y position
      if (!typeNodesByY.has(yKey)) {
        typeNodesByY.set(yKey, []);
      }
      typeNodesByY.get(yKey).push({ typeNode, typeId });
    });

    // Store actual rendered positions for link calculations
    const typeNodePositions = new Map();
    const minVerticalSpacing = 120; // Increased spacing to account for text labels

    // Process type nodes with vertical spacing
    typeNodesByY.forEach((nodesAtY, yKey) => {
      // Sort by x position (vertical in tree)
      nodesAtY.sort((a, b) => a.typeNode.x - b.typeNode.x);

      nodesAtY.forEach((item, index) => {
        const { typeNode, typeId } = item;
        // Calculate vertical offset to prevent overlaps
        const verticalOffset = index * minVerticalSpacing;
        const renderedX = typeNode.x + verticalOffset;
        const renderedY = typeNode.y + 350; // Increased horizontal offset to avoid main nodes

        // Store actual position for links
        typeNodePositions.set(typeId, { x: renderedX, y: renderedY });

        const typeGroup = this.g
          .append("g")
          .attr("class", "semantic-node type-node clickable-semantic-node")
          .attr("transform", `translate(${renderedY},${renderedX})`)
          .style("cursor", "pointer")
          .datum({ typeId: typeId, isType: true });

        typeGroup
          .append("circle")
          .attr("r", 6)
          .attr("fill", "#ff7b72")
          .attr("stroke", "#fff")
          .attr("stroke-width", 2);

        // Add background rectangle for text label
        const labelText = `T:${typeNode.name.substring(0, 15)}`;
        const textElement = typeGroup
          .append("text")
          .attr("x", 12)
          .attr("y", 4)
          .attr("fill", "#ff7b72")
          .attr("font-size", "10px")
          .attr("font-weight", "600")
          .text(labelText);

        // Get text bounding box and add background (insert before text so it appears behind)
        const textBBox = textElement.node().getBBox();
        typeGroup
          .insert("rect", () => textElement.node())
          .attr("x", textBBox.x - 2)
          .attr("y", textBBox.y - 1)
          .attr("width", textBBox.width + 4)
          .attr("height", textBBox.height + 2)
          .attr("fill", "rgba(0, 0, 0, 0.7)")
          .attr("rx", 2);

        // Make type node clickable - show type details
        typeGroup.on("click", (e) => {
          e.stopPropagation();
          const typeInfo = this.semanticData.types[typeId];
          if (typeInfo && this.onNodeHover) {
            this.onNodeHover(typeInfo);
          }
        });

        // Add hover effect for type node
        typeGroup
          .on("mouseover", (e) => {
            e.stopPropagation();
            typeGroup.classed("active-semantic", true);
          })
          .on("mouseout", (e) => {
            e.stopPropagation();
            typeGroup.classed("active-semantic", false);
          });

        // Draw links from nodes to type (use rendered position)
        const nodesWithType = nodesByTypeId.get(typeId) || [];
        nodesWithType.forEach((sourceNode) => {
          typeLinks.push({
            source: { x: sourceNode.x, y: sourceNode.y },
            target: { x: renderedX, y: renderedY },
          });
        });

        // Draw links between nodes that share the same type (dashed links between nodes)
        if (nodesWithType.length > 1) {
          for (let i = 0; i < nodesWithType.length; i++) {
            for (let j = i + 1; j < nodesWithType.length; j++) {
              typeLinks.push({
                source: { x: nodesWithType[i].x, y: nodesWithType[i].y },
                target: { x: nodesWithType[j].x, y: nodesWithType[j].y },
              });
            }
          }
        }
      });
    });

    // Create symbol nodes visualization with collision avoidance
    // Group symbol nodes by y position to handle overlaps
    const symbolNodesByY = new Map();
    symbolNodes.forEach((symbolNode, symbolId) => {
      const yKey = Math.round(symbolNode.y / 20) * 20; // Group by rounded y position
      if (!symbolNodesByY.has(yKey)) {
        symbolNodesByY.set(yKey, []);
      }
      symbolNodesByY.get(yKey).push({ symbolNode, symbolId });
    });

    // Store actual rendered positions for link calculations
    const symbolNodePositions = new Map();
    // Reuse minVerticalSpacing from above (120px)

    // Process symbol nodes with vertical spacing
    symbolNodesByY.forEach((nodesAtY, yKey) => {
      // Sort by x position (vertical in tree)
      nodesAtY.sort((a, b) => a.symbolNode.x - b.symbolNode.x);

      nodesAtY.forEach((item, index) => {
        const { symbolNode, symbolId } = item;
        // Calculate vertical offset to prevent overlaps
        const verticalOffset = index * minVerticalSpacing;
        const renderedX = symbolNode.x + verticalOffset;
        const renderedY = symbolNode.y - 350; // Increased horizontal offset to avoid main nodes

        // Store actual position for links
        symbolNodePositions.set(symbolId, { x: renderedX, y: renderedY });

        const symbolGroup = this.g
          .append("g")
          .attr("class", "semantic-node symbol-node clickable-semantic-node")
          .attr("transform", `translate(${renderedY},${renderedX})`)
          .style("cursor", "pointer")
          .datum({ symbolId: symbolId, isSymbol: true });

        symbolGroup
          .append("circle")
          .attr("r", 6)
          .attr("fill", "#79c0ff")
          .attr("stroke", "#fff")
          .attr("stroke-width", 2);

        // Add background rectangle for text label
        const labelText = `S:${symbolNode.name.substring(0, 15)}`;
        const textElement = symbolGroup
          .append("text")
          .attr("x", -60)
          .attr("y", 4)
          .attr("text-anchor", "end")
          .attr("fill", "#79c0ff")
          .attr("font-size", "10px")
          .attr("font-weight", "600")
          .text(labelText);

        // Get text bounding box and add background (insert before text so it appears behind)
        const textBBox = textElement.node().getBBox();
        symbolGroup
          .insert("rect", () => textElement.node())
          .attr("x", textBBox.x - 2)
          .attr("y", textBBox.y - 1)
          .attr("width", textBBox.width + 4)
          .attr("height", textBBox.height + 2)
          .attr("fill", "rgba(0, 0, 0, 0.7)")
          .attr("rx", 2);

        // Make symbol node clickable - show symbol details
        symbolGroup.on("click", (e) => {
          e.stopPropagation();
          const symbolInfo = this.semanticData.symbols[symbolId];
          if (symbolInfo && this.onNodeHover) {
            this.onNodeHover(symbolInfo);
          }
        });

        // Add hover effect for symbol node
        symbolGroup
          .on("mouseover", (e) => {
            e.stopPropagation();
            symbolGroup.classed("active-semantic", true);
          })
          .on("mouseout", (e) => {
            e.stopPropagation();
            symbolGroup.classed("active-semantic", false);
          });

        // Draw links from nodes to symbol (use rendered position)
        const nodesWithSymbol = nodesBySymbolId.get(symbolId) || [];
        nodesWithSymbol.forEach((sourceNode) => {
          symbolLinks.push({
            source: { x: sourceNode.x, y: sourceNode.y },
            target: { x: renderedX, y: renderedY },
          });
        });

        // Draw links between nodes that share the same symbol (dashed links between nodes)
        if (nodesWithSymbol.length > 1) {
          for (let i = 0; i < nodesWithSymbol.length; i++) {
            for (let j = i + 1; j < nodesWithSymbol.length; j++) {
              symbolLinks.push({
                source: { x: nodesWithSymbol[i].x, y: nodesWithSymbol[i].y },
                target: { x: nodesWithSymbol[j].x, y: nodesWithSymbol[j].y },
              });
            }
          }
        }
      });
    });

    // Draw type links (dashed, red) - ensure they're visible
    if (typeLinks.length > 0) {
      this.g
        .selectAll(".semantic-link.type-link")
        .data(typeLinks)
        .enter()
        .append("path")
        .attr("class", "semantic-link type-link")
        .attr("fill", "none")
        .attr("stroke", "#ff7b72")
        .attr("stroke-width", 2)
        .attr("stroke-dasharray", "8,4")
        .attr("opacity", 0.7)
        .attr("pointer-events", "none")
        .attr("d", (link) => {
          return d3
            .linkHorizontal()
            .x((d) => d.y)
            .y((d) => d.x)(link);
        });
    }

    // Draw symbol links (dashed, blue) - ensure they're visible
    if (symbolLinks.length > 0) {
      this.g
        .selectAll(".semantic-link.symbol-link")
        .data(symbolLinks)
        .enter()
        .append("path")
        .attr("class", "semantic-link symbol-link")
        .attr("fill", "none")
        .attr("stroke", "#79c0ff")
        .attr("stroke-width", 2)
        .attr("stroke-dasharray", "8,4")
        .attr("opacity", 0.7)
        .attr("pointer-events", "none")
        .attr("d", (link) => {
          return d3
            .linkHorizontal()
            .x((d) => d.y)
            .y((d) => d.x)(link);
        });
    }
  }

  // Helper: Check if range1 contains range2 (range1 is the parent, range2 is the child/token)
  rangeContains(range1, range2) {
    if (
      !range1 ||
      !range2 ||
      !range1.start ||
      !range1.end ||
      !range2.start ||
      !range2.end
    ) {
      return false;
    }
    if (
      !Array.isArray(range1.start) ||
      !Array.isArray(range1.end) ||
      !Array.isArray(range2.start) ||
      !Array.isArray(range2.end)
    ) {
      return false;
    }

    const r1Start = range1.start;
    const r1End = range1.end;
    const r2Start = range2.start;
    const r2End = range2.end;

    // Check if range1 contains range2
    // range1 contains range2 if:
    // - range1 starts before or at the same position as range2
    // - range1 ends after or at the same position as range2

    const startBeforeOrEqual =
      r1Start[0] < r2Start[0] ||
      (r1Start[0] === r2Start[0] && r1Start[1] <= r2Start[1]);
    const endAfterOrEqual =
      r1End[0] > r2End[0] || (r1End[0] === r2End[0] && r1End[1] >= r2End[1]);

    return startBeforeOrEqual && endAfterOrEqual;
  }

  // Helper: Find node in D3 data that matches source range
  highlightNodeByRange(range) {
    if (!this.g || !this.svg) return;

    this.g.selectAll(".node").classed("active", false);

    if (!range) return;

    // Find the matching node(s) - prefer exact range match, then containing nodes, then start position match
    let targetNode = null;
    let bestMatch = null;
    let bestScore = -1;
    const containingNodes = [];
    const exactMatches = [];
    const startMatches = [];

    this.g.selectAll(".node").each((d) => {
      const r = d.data.raw.range;
      if (!r || !r.start || !r.end) return;

      // Check for exact range match (start and end)
      if (
        range.start &&
        range.end &&
        Array.isArray(r.start) &&
        Array.isArray(r.end) &&
        Array.isArray(range.start) &&
        Array.isArray(range.end)
      ) {
        // Exact match
        if (
          r.start[0] === range.start[0] &&
          r.start[1] === range.start[1] &&
          r.end[0] === range.end[0] &&
          r.end[1] === range.end[1]
        ) {
          exactMatches.push({ node: d, range: r });
          return; // Skip to next node
        }

        // Check if this node contains the token range
        if (this.rangeContains(r, range)) {
          containingNodes.push({ node: d, range: r });
          return; // Skip to next node
        }
      }

      // Check for start position match
      if (
        r.start &&
        range.start &&
        Array.isArray(r.start) &&
        Array.isArray(range.start)
      ) {
        if (r.start[0] === range.start[0] && r.start[1] === range.start[1]) {
          startMatches.push({ node: d, range: r });
        }
      }
    });

    // Priority: exact match > containing node (smallest) > start match
    if (exactMatches.length > 0) {
      bestMatch = exactMatches[0].node;
      bestScore = 100;
    } else if (containingNodes.length > 0) {
      // Find the smallest containing node (most specific parent)
      // Calculate range size: (endLine - startLine) * 10000 + (endCol - startCol)
      containingNodes.sort((a, b) => {
        const aSize =
          (a.range.end[0] - a.range.start[0]) * 10000 +
          (a.range.end[1] - a.range.start[1]);
        const bSize =
          (b.range.end[0] - b.range.start[0]) * 10000 +
          (b.range.end[1] - b.range.start[1]);
        return aSize - bSize; // Smaller range = more specific parent
      });
      bestMatch = containingNodes[0].node;
      bestScore = 75;
    } else if (startMatches.length > 0) {
      bestMatch = startMatches[0].node;
      bestScore = 50;
    }

    // Highlight all matching nodes (exact matches, containing nodes, or start matches)
    const nodesToHighlight = new Set();

    // Add exact matches
    exactMatches.forEach(({ node }) => nodesToHighlight.add(node));

    // Add containing nodes (highlight all, but zoom to smallest)
    containingNodes.forEach(({ node }) => nodesToHighlight.add(node));

    // Add start matches if no exact or containing matches
    if (exactMatches.length === 0 && containingNodes.length === 0) {
      startMatches.forEach(({ node }) => nodesToHighlight.add(node));
    }

    // Highlight all matching nodes
    this.g
      .selectAll(".node")
      .filter((d) => nodesToHighlight.has(d))
      .classed("active", true);

    // Use the best match for zooming
    targetNode = bestMatch;

    // Zoom to the node if found
    if (targetNode) {
      const nodeX = targetNode.x;
      const nodeY = targetNode.y;

      // Get SVG dimensions
      const svgWidth = this.svg.node().clientWidth;
      const svgHeight = this.svg.node().clientHeight;

      // Calculate target transform to center the node
      // In D3 tree layout: x is vertical, y is horizontal
      const targetScale = 1.5; // Zoom in a bit
      const targetX = svgWidth / 2 - nodeY * targetScale;
      const targetY = svgHeight / 2 - nodeX * targetScale;

      // Create animated transition
      this.svg
        .transition()
        .duration(600)
        .ease(d3.easeCubicInOut)
        .call(
          this.zoom.transform,
          d3.zoomIdentity.translate(targetX, targetY).scale(targetScale)
        );
    }
  }

  // Helper: Highlight nodes by typeId
  highlightNodeByTypeId(typeId) {
    if (!this.g || !this.svg || !typeId) return null;

    this.g.selectAll(".node").classed("active", false);
    this.g.selectAll(".semantic-node").classed("active-semantic", false);

    let foundNode = null;

    // Highlight tree nodes with this typeId
    this.g
      .selectAll(".node")
      .filter((d) => {
        const raw = d.data.raw;
        const nodeTypeId = raw.typeId !== undefined ? raw.typeId : raw.type_id;
        return raw && nodeTypeId === typeId;
      })
      .classed("active", true)
      .each((d) => {
        if (!foundNode) foundNode = d;
      });

    // Highlight type node
    this.g
      .selectAll(".type-node")
      .filter((d) => {
        return d && d.typeId === typeId;
      })
      .classed("active-semantic", true);

    // Zoom to the first found node if available
    if (foundNode) {
      const nodeX = foundNode.x;
      const nodeY = foundNode.y;

      // Get SVG dimensions
      const svgWidth = this.svg.node().clientWidth;
      const svgHeight = this.svg.node().clientHeight;

      // Calculate target transform to center the node
      const targetScale = 1.5;
      const targetX = svgWidth / 2 - nodeY * targetScale;
      const targetY = svgHeight / 2 - nodeX * targetScale;

      // Create animated transition
      this.svg
        .transition()
        .duration(600)
        .ease(d3.easeCubicInOut)
        .call(
          this.zoom.transform,
          d3.zoomIdentity.translate(targetX, targetY).scale(targetScale)
        );
    }

    return foundNode;
  }

  // Helper: Highlight nodes by symbolId
  highlightNodeBySymbolId(symbolId) {
    if (!this.g || !this.svg || symbolId === undefined) return null;

    this.g.selectAll(".node").classed("active", false);
    this.g.selectAll(".semantic-node").classed("active-semantic", false);

    let foundNode = null;

    // Highlight tree nodes with this symbolId
    this.g
      .selectAll(".node")
      .filter((d) => {
        const raw = d.data.raw;
        const nodeSymbolId =
          raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
        const nodeSymbolIds = raw.symbolIds || raw.symbol_ids;
        return (
          raw &&
          (nodeSymbolId === symbolId ||
            (nodeSymbolIds &&
              Array.isArray(nodeSymbolIds) &&
              nodeSymbolIds.includes(symbolId)))
        );
      })
      .classed("active", true)
      .each((d) => {
        if (!foundNode) foundNode = d;
      });

    // Highlight symbol node
    this.g
      .selectAll(".symbol-node")
      .filter((d) => {
        return d && d.symbolId === symbolId;
      })
      .classed("active-semantic", true);

    // Zoom to the first found node if available
    if (foundNode) {
      const nodeX = foundNode.x;
      const nodeY = foundNode.y;

      // Get SVG dimensions
      const svgWidth = this.svg.node().clientWidth;
      const svgHeight = this.svg.node().clientHeight;

      // Calculate target transform to center the node
      const targetScale = 1.5;
      const targetX = svgWidth / 2 - nodeY * targetScale;
      const targetY = svgHeight / 2 - nodeX * targetScale;

      // Create animated transition
      this.svg
        .transition()
        .duration(600)
        .ease(d3.easeCubicInOut)
        .call(
          this.zoom.transform,
          d3.zoomIdentity.translate(targetX, targetY).scale(targetScale)
        );
    }

    return foundNode;
  }

  // Navigate to a specific node by its data with animation
  navigateToNode(nodeData) {
    if (!this.g || !nodeData) {
      console.log("navigateToNode: Missing g or nodeData", {
        g: !!this.g,
        nodeData,
      });
      return false;
    }

    // Find the node in the tree by matching range or other unique properties
    // Collect ALL matching nodes and find the best match
    const matchingNodes = [];

    console.log("Searching for node:", nodeData);
    console.log("Node data range:", nodeData.range);
    console.log("Node data kind:", nodeData.kind);
    console.log(
      "Node data typeId:",
      nodeData.typeId !== undefined ? nodeData.typeId : nodeData.type_id
    );
    console.log(
      "Node data symbolId:",
      nodeData.symbolId !== undefined ? nodeData.symbolId : nodeData.symbol_id
    );

    this.g.selectAll(".node").each((d) => {
      if (this.nodesMatch(d.data.raw, nodeData)) {
        matchingNodes.push(d);
        console.log("Found matching node:", {
          kind: d.data.raw.kind,
          range: d.data.raw.range,
          typeId:
            d.data.raw.typeId !== undefined
              ? d.data.raw.typeId
              : d.data.raw.type_id,
          symbolId:
            d.data.raw.symbolId !== undefined
              ? d.data.raw.symbolId
              : d.data.raw.symbol_id,
        });
      }
    });

    console.log(`Found ${matchingNodes.length} matching nodes`);

    if (matchingNodes.length === 0) {
      console.log("No matching node found in tree");
      return false;
    }

    // If multiple matches, find the one with the best match score
    let targetNode = matchingNodes[0];
    if (matchingNodes.length > 1) {
      console.log("Multiple matches found, selecting best match");
      // Score each match - prefer exact range matches
      let bestScore = -1;
      for (const node of matchingNodes) {
        let score = 0;
        const raw = node.data.raw;

        // Range match is most important
        if (nodeData.range && raw.range) {
          const r1 = nodeData.range;
          const r2 = raw.range;
          if (
            r1.start &&
            r2.start &&
            r1.end &&
            r2.end &&
            Array.isArray(r1.start) &&
            Array.isArray(r2.start) &&
            Array.isArray(r1.end) &&
            Array.isArray(r2.end)
          ) {
            if (
              r1.start[0] === r2.start[0] &&
              r1.start[1] === r2.start[1] &&
              r1.end[0] === r2.end[0] &&
              r1.end[1] === r2.end[1]
            ) {
              score += 100; // Perfect range match
            } else if (
              r1.start[0] === r2.start[0] &&
              r1.start[1] === r2.start[1]
            ) {
              score += 50; // Start only match
            }
          }
        }

        // TypeId match
        const typeId1 =
          nodeData.typeId !== undefined ? nodeData.typeId : nodeData.type_id;
        const typeId2 = raw.typeId !== undefined ? raw.typeId : raw.type_id;
        if (
          typeId1 !== undefined &&
          typeId2 !== undefined &&
          typeId1 === typeId2
        ) {
          score += 20;
        }

        // SymbolId match
        const symbolId1 =
          nodeData.symbolId !== undefined
            ? nodeData.symbolId
            : nodeData.symbol_id;
        const symbolId2 =
          raw.symbolId !== undefined ? raw.symbolId : raw.symbol_id;
        if (
          symbolId1 !== undefined &&
          symbolId2 !== undefined &&
          symbolId1 === symbolId2
        ) {
          score += 20;
        }

        // Value match
        if (
          nodeData.value !== undefined &&
          raw.value !== undefined &&
          nodeData.value === raw.value
        ) {
          score += 10;
        }

        // Name match
        if (
          nodeData.name !== undefined &&
          raw.name !== undefined &&
          nodeData.name === raw.name
        ) {
          score += 10;
        }

        if (score > bestScore) {
          bestScore = score;
          targetNode = node;
        }
      }
      console.log("Selected node with best score:", bestScore, {
        kind: targetNode.data.raw.kind,
        range: targetNode.data.raw.range,
        typeId:
          targetNode.data.raw.typeId !== undefined
            ? targetNode.data.raw.typeId
            : targetNode.data.raw.type_id,
        symbolId:
          targetNode.data.raw.symbolId !== undefined
            ? targetNode.data.raw.symbolId
            : targetNode.data.raw.symbol_id,
      });
    }

    // Verify the selected node matches the requested node data exactly
    if (!this.nodesMatch(targetNode.data.raw, nodeData)) {
      console.error("ERROR: Selected node does not match requested node data!");
      console.error("Requested:", nodeData);
      console.error("Selected:", targetNode.data.raw);
      return false;
    }

    // Clear previous highlights
    this.g.selectAll(".node").classed("active", false);

    // Highlight the target node
    this.g
      .selectAll(".node")
      .filter((d) => d === targetNode)
      .classed("active", true);

    // Get the node's position - ensure we're using the correct node
    const nodeX = targetNode.x;
    const nodeY = targetNode.y;

    console.log("Navigating to node at position:", { x: nodeX, y: nodeY });
    console.log("Target node data:", {
      kind: targetNode.data.raw.kind,
      range: targetNode.data.raw.range,
      typeId:
        targetNode.data.raw.typeId !== undefined
          ? targetNode.data.raw.typeId
          : targetNode.data.raw.type_id,
      symbolId:
        targetNode.data.raw.symbolId !== undefined
          ? targetNode.data.raw.symbolId
          : targetNode.data.raw.symbol_id,
    });

    // Get SVG dimensions
    const svgWidth = this.svg.node().clientWidth;
    const svgHeight = this.svg.node().clientHeight;

    // Calculate target transform to center the node
    // In D3 tree layout: x is vertical, y is horizontal
    // We want to center the node, so: translate = center - (nodePosition * scale)
    const targetScale = 1.5; // Zoom in a bit
    const targetX = svgWidth / 2 - nodeY * targetScale;
    const targetY = svgHeight / 2 - nodeX * targetScale;

    console.log("Target transform:", {
      x: targetX,
      y: targetY,
      scale: targetScale,
    });

    // Create animated transition
    this.svg
      .transition()
      .duration(800)
      .ease(d3.easeCubicInOut)
      .call(
        this.zoom.transform,
        d3.zoomIdentity.translate(targetX, targetY).scale(targetScale)
      );

    // Add a pulse animation to the node
    const nodeElement = this.g
      .selectAll(".node")
      .filter((d) => d === targetNode)
      .node();

    if (nodeElement) {
      // Add pulse effect
      const circle = nodeElement.querySelector("circle");
      if (circle) {
        const originalRadius = parseFloat(circle.getAttribute("r"));
        d3.select(circle)
          .transition()
          .duration(200)
          .attr("r", originalRadius * 1.5)
          .transition()
          .duration(200)
          .attr("r", originalRadius)
          .transition()
          .duration(200)
          .attr("r", originalRadius * 1.3)
          .transition()
          .duration(200)
          .attr("r", originalRadius);
      }
    }

    return true;
  }

  // Helper: Check if two node data objects match - check ALL properties for exact match
  nodesMatch(node1, node2) {
    if (!node1 || !node2) return false;

    // 1. Range matching (MOST IMPORTANT) - require BOTH start AND end to match exactly
    if (node1.range && node2.range) {
      const r1 = node1.range;
      const r2 = node2.range;

      if (
        r1.start &&
        r2.start &&
        Array.isArray(r1.start) &&
        Array.isArray(r2.start) &&
        r1.start.length >= 2 &&
        r2.start.length >= 2
      ) {
        const startMatch =
          r1.start[0] === r2.start[0] && r1.start[1] === r2.start[1];

        if (startMatch) {
          // If both have end, require end to match exactly
          if (
            r1.end &&
            r2.end &&
            Array.isArray(r1.end) &&
            Array.isArray(r2.end) &&
            r1.end.length >= 2 &&
            r2.end.length >= 2
          ) {
            const endMatch = r1.end[0] === r2.end[0] && r1.end[1] === r2.end[1];
            if (!endMatch) return false; // End doesn't match - not the same node
          }
          // Start matches, continue checking other properties
        } else {
          return false; // Start doesn't match - not the same node
        }
      } else {
        return false; // Invalid ranges - can't match
      }
    } else if (node1.range || node2.range) {
      // One has range, other doesn't - can't be the same node
      return false;
    }
    // If neither has range, continue checking other properties

    // 2. Kind MUST match
    if (node1.kind !== node2.kind) {
      return false;
    }

    // 3. TypeId must match if both have it
    const typeId1 = node1.typeId !== undefined ? node1.typeId : node1.type_id;
    const typeId2 = node2.typeId !== undefined ? node2.typeId : node2.type_id;
    if (typeId1 !== undefined && typeId2 !== undefined) {
      if (typeId1 !== typeId2) return false;
    } else if (typeId1 !== typeId2) {
      // One has typeId, other doesn't - can't be the same node
      return false;
    }

    // 4. SymbolId must match if both have it
    const symbolId1 =
      node1.symbolId !== undefined ? node1.symbolId : node1.symbol_id;
    const symbolId2 =
      node2.symbolId !== undefined ? node2.symbolId : node2.symbol_id;
    if (symbolId1 !== undefined && symbolId2 !== undefined) {
      if (symbolId1 !== symbolId2) return false;
    } else if (symbolId1 !== symbolId2) {
      // One has symbolId, other doesn't - can't be the same node
      return false;
    }

    // 5. Value must match if both have it
    if (node1.value !== undefined && node2.value !== undefined) {
      if (node1.value !== node2.value) return false;
    } else if (node1.value !== node2.value) {
      // One has value, other doesn't - can't be the same node
      return false;
    }

    // 6. Name must match if both have it
    if (node1.name !== undefined && node2.name !== undefined) {
      if (node1.name !== node2.name) return false;
    } else if (node1.name !== node2.name) {
      // One has name, other doesn't - can't be the same node
      return false;
    }

    // All checked properties match - this is the same node
    return true;
  }

  transformToHierarchy(node, key = "Root") {
    if (!node || typeof node !== "object") return null;

    const name = node.kind || key;
    const children = [];

    Object.keys(node).forEach((k) => {
      if (k === "kind" || k === "range" || k === "typeId" || k === "symbolId")
        return;

      const val = node[k];
      if (Array.isArray(val)) {
        val.forEach((child, i) => {
          const c = this.transformToHierarchy(child, `${k}[${i}]`);
          if (c) children.push(c);
        });
      } else if (typeof val === "object" && val !== null) {
        const c = this.transformToHierarchy(val, k);
        if (c) children.push(c);
      } else {
        // Primitive value -> Leaf
        children.push({ name: `${k}: ${val}`, raw: {} });
      }
    });

    return { name, children: children.length ? children : null, raw: node };
  }
}
