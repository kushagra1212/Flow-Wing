#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MAX_REQUEST_SIZE 10240

typedef void (*CustomRequestHandler)(const char *request,
                               const char *response);
                               
  typedef void (*RequestHandler)(int client_socket, const char *request,
                               const char *endpoint, CustomRequestHandler custom_handler);
typedef struct Route {
  char method[16];
  char path[256];
  RequestHandler handler;
  CustomRequestHandler custom_handler;
  struct Route *next;
} Route;

static Route *routes = NULL;
static RequestHandler middleware = NULL;
static CustomRequestHandler middlewareCustom = NULL;

void set_route(const char *method, const char *path, RequestHandler handler, CustomRequestHandler custom_handler) {
  Route *new_route = (Route *)malloc(sizeof(Route));
  strncpy(new_route->method, method, sizeof(new_route->method) - 1);
  strncpy(new_route->path, path, sizeof(new_route->path) - 1);
  new_route->handler = handler;
  new_route->custom_handler = custom_handler;
  
  new_route->next = routes;
  routes = new_route;
}

void set_middleware(RequestHandler mw, CustomRequestHandler mwCustom) { middleware = mw; middlewareCustom = mwCustom; }




char* send_response(int client_socket, const char *status, const char *content_type, const char *body, int keep_alive, size_t _content_length ) {
    if (!status || !content_type) {
        perror("Invalid status or content_type provided");
        return "Error: Invalid status or content_type provided";
    }

    // Determine body length, handle null or empty body
    size_t body_length =_content_length ? _content_length: ((body != NULL) ? strlen(body) : 0);

    // Estimate size for the full response, including headers
    size_t response_size = 512 + body_length; // A rough estimate for the headers + body
    char *response = (char *)malloc(response_size);
    if (!response) {
        perror("malloc");
        return "Error: Memory allocation failed";
    }

    // Get current time for the Date header
    char date_header[128];
    time_t now = time(NULL);
    struct tm *tm_info = gmtime(&now);
    if (!strftime(date_header, sizeof(date_header), "%a, %d %b %Y %H:%M:%S GMT", tm_info)) {
        free(response);
        perror("strftime");
        return "Error: Failed to format the date";
    }

    // Set the connection type: Keep-Alive or close
    const char *connection_type = keep_alive ? "Keep-Alive" : "close";
    const char *keep_alive_header = keep_alive ? "Keep-Alive: timeout=5, max=100\r\n" : "";

    // Create the full HTTP response with headers
    int header_length = snprintf(response, response_size,
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: %s\r\n"
        "%s"  // This will insert the Keep-Alive header if necessary
        "Server: FlowWingServer/0.1\r\n"
        "Date: %s\r\n"
        "\r\n",
        status, content_type, body_length, connection_type, keep_alive_header, date_header);

    if (header_length < 0) {
        free(response);
        return "Error: Failed to format response headers";
    }

    // Check if the buffer size is sufficient, reallocate if necessary
    if ((size_t)(header_length + body_length) >= response_size) {
        response_size = header_length + body_length + 1; // +1 for null terminator
        char *new_response = (char *)realloc(response, response_size);
        if (!new_response) {
            free(response);
            perror("realloc");
            return "Error: Memory reallocation failed";
        }
        response = new_response;
    }

    // Append the body to the response (if any)
    if (body && body_length > 0) {
        memcpy(response + header_length, body, body_length);
    }

    // Total response length (headers + body)
    size_t total_response_length = header_length + body_length;

    // Send the response
    ssize_t bytes_sent = send(client_socket, response, total_response_length, 0);
    if (bytes_sent == -1) {
        free(response);
     // Close the socket unless it's a Keep-Alive connection
    if (!keep_alive) {
        close(client_socket);
    }
        perror("After send");
        return "Error: Failed to send response";
    }

    // Clean up
    free(response);

    // Close the socket unless it's a Keep-Alive connection
    if (!keep_alive) {
        close(client_socket);
    }

    // No errors, return NULL
    return NULL;
}

void parse_http_request(const char *request, char *method, char *endpoint) {
  sscanf(request, "%s %s", method, endpoint);
}

char *read_file(const char *path, size_t *out_length) {
    // Check if the file exists before trying to open it
    if (access(path, F_OK) == -1) {
        perror("File does not exist");
        return NULL;
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("File open failed");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *out_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(*out_length);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, *out_length, file);
    if (bytesRead != *out_length) {
        free(buffer);
        fclose(file);
        fprintf(stderr, "Error reading file: Expected %zu bytes, but got %zu\n", *out_length, bytesRead);
        return NULL;
    }

    fclose(file);
    return buffer;
}



void handle_request(int client_socket, const char *request) {
  char method[16];
  char endpoint[256];
  parse_http_request(request, method, endpoint);

  if (middleware) {
    middleware(client_socket, request, endpoint, middlewareCustom);
    fflush(stdout);
  }

  Route *current = routes;
  while (current) {
    if (strcmp(current->method, method) == 0 &&
        strcmp(current->path, endpoint) == 0) {
      current->handler(client_socket, request, endpoint, current->custom_handler);
      return;
    }
    current = current->next;
  }

      // Get the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        send_response(client_socket, "500 Internal Server Error", "text/plain", "Failed to get current working directory", 1,0);
        return;
    }

    // Combine the current working directory with the endpoint
    char *file_path = malloc(strlen(cwd) + strlen(endpoint) + 2); // +2 for '/' and null terminator
    if (!file_path) {
        send_response(client_socket, "500 Internal Server Error", "text/plain", "Memory allocation failed", 1,0);
        return;
    }

        // Only serve files from the "static" folder
    const char *static_folder = "/static";
    
    // Check if the requested endpoint starts with "/static"
    if (strncmp(endpoint, static_folder, strlen(static_folder)) != 0) {
        send_response(client_socket, "403 Forbidden", "text/plain", "Access to requested resource is forbidden", 1,0);
        return;
    }

    // Construct the full file path
    sprintf(file_path, "%s%s", cwd, endpoint);


    // Read the file content
    size_t file_length;
    char *file_content = read_file(file_path, &file_length);
    free(file_path);

    if (file_content) {
        // Determine the MIME type based on the file extension
        const char *mime_type = "text/plain"; // Default MIME type
        if (strstr(endpoint, ".html")) {
            mime_type = "text/html";
        } else if (strstr(endpoint, ".css")) {
            mime_type = "text/css";
        } else if (strstr(endpoint, ".js")) {
            mime_type = "application/javascript";
        } else if (strstr(endpoint, ".jpg") || strstr(endpoint, ".jpeg")) {
            mime_type = "image/jpeg";
        } else if (strstr(endpoint, ".png")) {
            mime_type = "image/png";
        } else if (strstr(endpoint, ".gif")) {
            mime_type = "image/gif";
        } else if (strstr(endpoint, ".svg")) {
            mime_type = "image/svg+xml";
        }

        // Send the response with the correct MIME type
        send_response(client_socket, "200 OK", mime_type, file_content, 1, file_length);
        free(file_content);
        return;
    }

    // No route matched and no static file found
    send_response(client_socket, "404 Not Found", "text/plain", "Page Not Found", 1,0);
}

void start_server(int port) {
  int server_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int new_socket;
  char buffer[MAX_REQUEST_SIZE] = {0};
  int opt = 1;

  // Create socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

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
  if (listen(server_fd, 10) < 0) {
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
    read(new_socket, buffer, MAX_REQUEST_SIZE);

    // Handle the request
    handle_request(new_socket, buffer);

    // Close the socket
    close(new_socket);
  }

  // Close the server socket
  close(server_fd);
}
void flush() { fflush(stdout); }