#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*RequestHandler)(int client_socket, const char *request,
                               const char *endpoint);

typedef struct Route {
  char method[16];
  char path[256];
  RequestHandler handler;
  struct Route *next;
} Route;

static Route *routes = NULL;
static RequestHandler middleware = NULL;

void set_route(const char *method, const char *path, RequestHandler handler) {
  Route *new_route = (Route *)malloc(sizeof(Route));
  strncpy(new_route->method, method, sizeof(new_route->method) - 1);
  strncpy(new_route->path, path, sizeof(new_route->path) - 1);
  new_route->handler = handler;
  new_route->next = routes;
  routes = new_route;
}

void set_middleware(RequestHandler mw) { middleware = mw; }

void send_response(int client_socket, const char *status,
                   const char *content_type, const char *body) {
  char response[1024];
  snprintf(response, sizeof(response),
           "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n%s",
           status, content_type, strlen(body), body);
  send(client_socket, response, strlen(response), 0);
}

void parse_http_request(const char *request, char *method, char *endpoint) {
  sscanf(request, "%s %s", method, endpoint);
}

void handle_request(int client_socket, const char *request) {
  char method[16];
  char endpoint[256];
  parse_http_request(request, method, endpoint);

  if (middleware) {
    middleware(client_socket, request, endpoint);
  }

  Route *current = routes;
  while (current) {
    if (strcmp(current->method, method) == 0 &&
        strcmp(current->path, endpoint) == 0) {
      current->handler(client_socket, request, endpoint);
      return;
    }
    current = current->next;
  }

  // No route matched
  send_response(client_socket, "404 Not Found", "text/plain", "Not Found");
}

void start_server() {
  int server_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int new_socket;
  char buffer[1024] = {0};
  int opt = 1;

  // Create socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  // Set SO_REUSEADDR option
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  // Bind the socket to the address
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Accept incoming connections
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // Read the request
    read(new_socket, buffer, 1024);

    // Handle the request
    handle_request(new_socket, buffer);

    // Close the socket
    close(new_socket);
  }

  // Close the server socket
  close(server_fd);
}
