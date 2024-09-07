#include "crow_all.h"
#include <functional>
#include <string>
#include <unordered_map>
// extern "C" {
// // Define a type for route handlers
// using RouteHandler = std::function<void(crow::SimpleApp &)>;

// class CrowWrapper {
// public:
//   CrowWrapper() : app_(crow::SimpleApp()) {}

//   // Set a route with a string path and a function handler
//   void addRoute(const std::string &path, RouteHandler handler) {
//     handlers_[path] = handler;
//   }

//   // Start the server on a given port
//   void run(int port) {
//     // for (const auto &handler : handlers_) {
//     //   handler.second(app_);
//     // }
//     app_.port(port).multithreaded().run();
//   }

//   // Set a custom port for the server
//   void setPort(int port) { port_ = port; }

// public:
//   crow::SimpleApp app_;
//   std::unordered_map<std::string, RouteHandler> handlers_;
//   int port_ = 18080;
// };

// CrowWrapper *g_crow_wrapper = nullptr;

// // void customRouteHandler(crow::SimpleApp &app) {
// //   CROW_ROUTE(app, "/")([]() { return "Hello from custom handler!"; });
// // }

// void create() {
//   if (!g_crow_wrapper) {
//     g_crow_wrapper = new CrowWrapper();
//   }
// }

// void destroy() {
//   delete g_crow_wrapper;
//   g_crow_wrapper = nullptr;
// }

// void addRoute(const char *path, char *(*func)()) {
//   if (g_crow_wrapper) {
//     CROW_ROUTE(g_crow_wrapper->app_, "/")
//     ([&]() {
//       // crow::json::wvalue response;
//       // response["message"] = "Custom API response!";
//       // response["status"] = "success";
//       return func();
//     });

//     // CROW_ROUTE(app, "/")
//     // ([&]() { return func(); });
//   }
// }

// void setPort(int port) {
//   if (g_crow_wrapper) {
//     g_crow_wrapper->setPort(port);
//   }
// }

// void runServer() {
//   if (g_crow_wrapper) {
//     g_crow_wrapper->run(g_crow_wrapper->port_);
//   }
// }
// }
// Template logic to add a route with variadic arguments

// Non-template wrapper for adding a route

// General template function for variadic arguments
// template <typename... Args>
// void addRouteImpl(
//     std::map<char *, std::function<crow::response(const crow::request *)>>
//         &handlers,
//     char *path, crow::response (*func)(Args...)) {
//   handlers[path] = [func](const crow::request &req) -> crow::response {
//     return crow::response(func(&req));
//   };
// }

extern "C" {

int port = 18080;
static crow::SimpleApp *app = nullptr;
// static std::map<char *, std::function<crow::response(const crow::request *)>>
//     handlers;

// Non-template function that can be called from C
// void addRoute(char *path, crow::response (*func)(const crow::request *)) {
//   addRouteImpl(handlers, path, func);
// }

void setPort(int _port) { port = _port; }
crow::SimpleApp *create() {
  app = new crow::SimpleApp();
  return app;
}

void addRoute(char *path, char *(*func)(std::string)) {
  std::string pathStr(path);

  if (pathStr.find("<str>") != std::string::npos) {
    app->route_dynamic(path)([func](std::string str) -> crow::response {
      return crow::response(func(str));
    });
  } else if (pathStr.find("<int>") != std::string::npos) {
    app->route_dynamic(path)([func](int num) -> crow::response {
      return crow::response(func(std::to_string(num)));
    });
  } else {
    app->route_dynamic(path)(
        [func]() -> crow::response { return crow::response(func("")); });
  }
}

void runServer() {
  // for (const auto &handler : handlers) {
  //   app->route_dynamic(handler.first)(handler.second);
  // }
  app->port(port).multithreaded().run();
}
}
// int main() {}

/*
 /Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing
 --F=crow.fg -O3 -L=/Users/apple/code/per/Flow-Wing/docs/local/modules -l=crow
 && build/bin/crow

*/
