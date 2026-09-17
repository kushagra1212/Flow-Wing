/* ===========================================================================
 * Flow-Wing site analytics
 *
 * One JSON document per event, POSTed to /track. The server stores it as-is,
 * so every field here is a field you can query later.
 *
 * Deliberately small. This tracks what THIS page can tell you — did anyone run
 * the playground, which install tab do people pick, does the expand button get
 * used — rather than a general-purpose analytics product.
 *
 * WHAT IT DOES NOT DO
 *
 *   No cookies, no localStorage identity, no cross-site anything. The session
 *   id lives in sessionStorage and dies with the tab, so it cannot follow
 *   anyone between visits. There is no fingerprinting: the fields below are
 *   the ones the browser hands out to render the page correctly anyway.
 * ======================================================================== */
(function () {
  "use strict";

  var ENDPOINT = "/track";

  /* Tab-scoped, not visitor-scoped. sessionStorage is cleared when the tab
     closes, so this groups events within one visit and nothing more. */
  var sid;
  try {
    sid = sessionStorage.getItem("fw_sid");
    if (!sid) {
      sid = "s_" + Date.now().toString(36) + "_" + Math.random().toString(36).slice(2, 10);
      sessionStorage.setItem("fw_sid", sid);
    }
  } catch (e) {
    sid = "s_nostore";            /* private mode: still works, just per-event */
  }

  /* Set fw_is_me=1 in your own browser so your visits are taggable and can be
     excluded from the dashboard. */
  var isSelf = false;
  try { isSelf = localStorage.getItem("fw_is_me") === "1"; } catch (e) {}

  var t0 = Date.now();
  var maxScroll = 0;

  function send(type, data) {
    var ev = {
      ts: Date.now(),
      type: type,
      sid: sid,
      path: location.pathname,
      ref: document.referrer || "",
      is_self: isSelf
    };
    if (data) for (var k in data) if (data.hasOwnProperty(k)) ev[k] = data[k];

    var payload = JSON.stringify(ev);

    /* sendBeacon survives the page being closed, which is the whole point for
       the exit event. It also never blocks navigation. fetch with keepalive is
       the fallback; both are fire-and-forget because a visitor can do nothing
       useful with a tracking failure. */
    try {
      if (navigator.sendBeacon) {
        navigator.sendBeacon(ENDPOINT, new Blob([payload], { type: "application/json" }));
        return;
      }
    } catch (e) {}
    try {
      fetch(ENDPOINT, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: payload,
        keepalive: true
      }).catch(function () {});
    } catch (e) {}
  }

  /* ---- page view ---- */
  send("view", {
    w: window.innerWidth,
    h: window.innerHeight,
    dpr: window.devicePixelRatio || 1,
    lang: navigator.language || "",
    tz_off: new Date().getTimezoneOffset(),
    ua: navigator.userAgent
  });

  /* ---- scroll depth, sampled not streamed ---- */
  window.addEventListener("scroll", function () {
    var doc = document.documentElement;
    var denom = doc.scrollHeight - window.innerHeight;
    if (denom <= 0) return;
    var pct = Math.round((window.scrollY / denom) * 100);
    if (pct > maxScroll) maxScroll = Math.min(100, pct);
  }, { passive: true });

  /* ---- the interactions that actually mean something on this page ---- */

  document.addEventListener("click", function (e) {
    var el = e.target && e.target.closest ? e.target.closest("a,button") : null;
    if (!el) return;

    /* download / docs CTAs */
    if (el.classList.contains("btn-primary"))   return send("cta", { cta: "download" });
    if (el.classList.contains("btn-secondary")) return send("cta", { cta: "docs" });

    /* platform tile in the download grid */
    var tile = el.closest ? el.closest(".platform-item") : null;
    if (tile) return send("platform_click", { os: (tile.textContent || "").trim().split("\n")[0] });

    /* playground */
    if (el.classList.contains("run-btn"))    return send("run_code");
    if (el.id === "expandBtn")               return send("playground_expand", { open: el.getAttribute("aria-expanded") === "true" });

    /* install commands */
    if (el.classList.contains("install-tab")) return send("install_tab", { os: el.getAttribute("data-os") || "" });
    if (el.classList.contains("install-copy")) {
      return send("install_copy", { where: el.id === "heroCopy" ? "hero" : "downloads" });
    }

    /* nav */
    if (el.closest && el.closest(".nav-links")) return send("nav", { to: el.getAttribute("href") || "" });
  }, true);

  /* ---- exit: how long, how far ---- */
  var sentExit = false;
  function exit() {
    if (sentExit) return;
    sentExit = true;
    send("exit", { ms: Date.now() - t0, scroll_pct: maxScroll });
  }
  /* pagehide is the reliable one; visibilitychange catches mobile tab switches
     that never fire pagehide at all. */
  window.addEventListener("pagehide", exit);
  document.addEventListener("visibilitychange", function () {
    if (document.visibilityState === "hidden") exit();
  });
})();
