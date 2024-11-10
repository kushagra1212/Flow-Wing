#include <corecrt.h>
#include <cstdint>
#include <cstdio>
#include <direct.h> // For _getcwd
#include <io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define getcwd _getcwd
#define snprintf _snprintf
#define close closesocket
#define access _access
#define F_OK 0

#pragma comment(lib, "Ws2_32.lib")
#if defined(_WIN32)
#define SHARED_LIB __stdcall __declspec(dllexport)
#else
#define SHARED_LIB
#endif
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_REQUEST_SIZE 10240

typedef void (*CustomRequestHandler)(const char *request, const char *response);

typedef void (*RequestHandler)(SOCKET client_socket, const char *request,
                               const char *endpoint,
                               CustomRequestHandler custom_handler);

typedef struct Route {
  char method[16];
  char path[256];
  RequestHandler handler;
  CustomRequestHandler custom_handler;
  struct Route *next;
} Route;

typedef struct {
  const char *extension;
  const char *mime_type;
} MimeType;

const MimeType mime_types[] = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    // Add more types as needed
};
const char *image_mime_types[] = {
    "image/jpeg", "image/png", "image/gif", "image/svg+xml",
    // Add more image types as needed
};
// Function to check if a given MIME type is an image type
bool isImage(const char *mime_type) {
  // List of image MIME types

  size_t num_image_types =
      sizeof(image_mime_types) / sizeof(image_mime_types[0]);

  // Compare the provided mime_type with known image MIME types
  for (size_t i = 0; i < num_image_types; ++i) {
    if (strcmp(mime_type, image_mime_types[i]) == 0) {
      return true; // The MIME type is an image type
    }
  }

  return false; // The MIME type is not an image type
}
const size_t mime_types_count = sizeof(mime_types) / sizeof(mime_types[0]);

const char *get_mime_type(const char *endpoint) {
  for (size_t i = 0; i < mime_types_count; i++) {
    if (strstr(endpoint, mime_types[i].extension) != NULL) {
      return mime_types[i].mime_type;
    }
  }
  return "text/plain"; // Default MIME type
}

static Route *routes = NULL;
static RequestHandler middleware = NULL;
static CustomRequestHandler middlewareCustom = NULL;

SHARED_LIB void set_route(const char *method, const char *path,
                          RequestHandler handler,
                          CustomRequestHandler custom_handler) {
  Route *new_route = (Route *)malloc(sizeof(Route));
  strncpy(new_route->method, method, sizeof(new_route->method) - 1);
  strncpy(new_route->path, path, sizeof(new_route->path) - 1);
  new_route->handler = handler;
  new_route->custom_handler = custom_handler;

  new_route->next = routes;
  routes = new_route;
}

SHARED_LIB void set_middleware(RequestHandler mw,
                               CustomRequestHandler mwCustom) {
  middleware = mw;
  middlewareCustom = mwCustom;
}

SHARED_LIB char *send_response(SOCKET client_socket, const char *status,
                               const char *content_type, const char *body,
                               int keep_alive, size_t _content_length) {

  if (!status || !content_type) {
    perror("Invalid status or content_type provided");
    return (char *)"Error: Invalid status or content_type provided";
  }

  size_t body_length = ((body != NULL) ? strlen(body) : 0);

  if (_content_length && isImage(content_type)) {
    body_length = _content_length;
  }

  size_t response_size = 512 + body_length;

  char *response = (char *)malloc(response_size);
  if (!response) {
    perror("malloc");
    return (char *)"Error: Memory allocation failed";
  }

  char date_header[128];
  time_t now = time(NULL);

  struct tm *tm_info = gmtime(&now);

  if (!strftime(date_header, sizeof(date_header), "%a, %d %b %Y %H:%M:%S GMT",
                tm_info)) {
    free(response);
    perror("strftime");
    return "Error: Failed to format the date";
  }
  const char *connection_type = keep_alive ? "Keep-Alive" : "close";
  const char *keep_alive_header =
      keep_alive ? "Keep-Alive: timeout=5, max=100\r\n" : "";

  int header_length = snprintf(response, response_size,
                               "HTTP/1.1 %s\r\n"
                               "Content-Type: %s\r\n"
                               "Content-Length: %zu\r\n"
                               "Connection: %s\r\n"
                               "%s"
                               "Server: FlowWingServer/0.1\r\n"
                               "Date: %s\r\n"
                               "\r\n",
                               status, content_type, body_length,
                               connection_type, keep_alive_header, date_header);

  if (header_length < 0) {
    free(response);
    return (char *)"Error: Failed to format response headers";
  }

  if ((size_t)(header_length + body_length) >= response_size) {
    response_size = header_length + body_length + 1;
    char *new_response = (char *)realloc(response, response_size);
    if (!new_response) {
      free(response);
      perror("realloc");
      return (char *)"Error: Memory reallocation failed";
    }
    response = new_response;
  }

  if (body && body_length > 0) {
    memcpy(response + header_length, body, body_length);
  }

  size_t total_response_length = header_length + body_length;
  int bytes_sent = send(client_socket, response, total_response_length, 0);
  if (bytes_sent == SOCKET_ERROR) {
    free(response);
    if (!keep_alive) {
      closesocket(client_socket);
    }
    perror("After send");
    return (char *)"Error: Failed to send response";
  }

  free(response);
  if (!keep_alive) {
    closesocket(client_socket);
  }

  return NULL;
}

SHARED_LIB void parse_http_request(const char *request, char *method,
                                   char *endpoint) {
  sscanf(request, "%s %s", method, endpoint);
}
SHARED_LIB char *read_file(const char *path, size_t &out_length) {
  // Check if the file exists before trying to open it
  out_length = 0;
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
  out_length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(out_length + 1);
  if (!buffer) {
    fclose(file);
    perror("Memory allocation failed");
    return NULL;
  }

  size_t bytesRead = fread(buffer, 1, out_length, file);
  if (bytesRead != out_length) {
    free(buffer);
    fclose(file);
    fprintf(stderr, "Error reading file: Expected %zu bytes, but got %zu\n",
            out_length, bytesRead);
    return NULL;
  }

  fclose(file);
  return buffer;
}

SHARED_LIB void handle_request(int client_socket, const char *request) {
  char method[16];
  char endpoint[256];

  size_t file_length = 0;
  parse_http_request(request, method, endpoint);

  if (middleware) {
    middleware(client_socket, request, endpoint, middlewareCustom);
    fflush(stdout);
  }

  Route *current = routes;
  while (current) {
    int8_t isValidMethod = strcmp(current->method, method) == 0;

    if (isValidMethod && strcmp(current->path, endpoint) == 0) {
      current->handler(client_socket, request, endpoint,
                       current->custom_handler);
      return;
    }

    // Check for wildcard match, like "/downloads/*"
    const char *wildcard_pos = strstr(current->path, "/*");
    if (wildcard_pos != NULL) {
      // Calculate the prefix length up to the "/*"
      size_t prefix_length = wildcard_pos - current->path;

      // Check if the endpoint matches the prefix and has a valid sub-path
      if (isValidMethod &&
          strncmp(endpoint, current->path, prefix_length) == 0 &&
          (endpoint[prefix_length] == '/' || endpoint[prefix_length] == '\0')) {
        current->handler(client_socket, request, endpoint,
                         current->custom_handler);
        return;
      }
    }

    current = current->next;
  }

  // Get the current working directory
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    send_response(client_socket, "500 Internal Server Error", "text/plain",
                  "Failed to get current working directory", 1, file_length);
    return;
  }

  // Combine the current working directory with the endpoint
  char *file_path = (char *)malloc(strlen(cwd) + strlen(endpoint) +
                                   2); // +2 for '\\' and null terminator
  if (!file_path) {
    send_response(client_socket, "500 Internal Server Error", "text/plain",
                  "Memory allocation failed", 1, file_length);
    return;
  }

  // Only serve files from the "static" folder
  const char *static_folder = "/static";
  // Check if the requested endpoint starts with "/static"
  if (strncmp(endpoint, static_folder, strlen(static_folder)) != 0) {
    send_response(client_socket, "403 Forbidden", "text/plain",
                  "Access to requested resource is forbidden", 1, file_length);
    free(file_path); // Free memory if access is forbidden
    return;
  }

  // Construct the full file path
  sprintf(file_path, "%s%s", cwd, endpoint);

  // Read the file content
  char *file_content = read_file(file_path, file_length);
  free(file_path);

  if (file_content) {
    // Determine the MIME type based on the file extension

    const char *mime_type = get_mime_type(endpoint);
    // Send the response with the correct MIME type
    send_response(client_socket, "200 OK", mime_type, file_content, 1,
                  file_length);
    free(file_content);
    return;
  }
  file_length = 0;
  // No route matched and no static file found
  send_response(client_socket, "404 Not Found", "text/plain", "Page Not Found",
                1, file_length);
}
SHARED_LIB void start_server(int port) {
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    perror("WSAStartup failed");
    exit(EXIT_FAILURE);
  }

  SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server_fd == INVALID_SOCKET) {
    perror("socket failed");
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt,
                 sizeof(opt)) == SOCKET_ERROR) {
    perror("setsockopt failed");
    closesocket(server_fd);
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) ==
      SOCKET_ERROR) {
    perror("bind failed");
    closesocket(server_fd);
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) == SOCKET_ERROR) {
    perror("listen failed");
    closesocket(server_fd);
    WSACleanup();
    exit(EXIT_FAILURE);
  }
  int new_socket;

  char buffer[MAX_REQUEST_SIZE] = {0};
  // Clear the buffer
  memset(buffer, 0, MAX_REQUEST_SIZE);

  while (1) {

    new_socket = accept(server_fd, NULL, NULL);
    if (new_socket == INVALID_SOCKET) {
      perror("accept failed");
      closesocket(server_fd);
      WSACleanup();
      exit(EXIT_FAILURE);
    }
    int bytes_read = recv(new_socket, buffer, MAX_REQUEST_SIZE, 0);
    if (bytes_read == SOCKET_ERROR) {
      perror("recv failed");
      // Handle the error as needed
    }
    handle_request(new_socket, buffer);

    closesocket(new_socket);
  }

  closesocket(server_fd);
  WSACleanup();
}

SHARED_LIB char *replace_all(const char *source, const char *search,
                             const char *replacement) {
  size_t search_len = strlen(search);
  size_t replacement_len = strlen(replacement);

  // Calculate the initial buffer size for the result
  size_t result_capacity = strlen(source) + 1; // Start with enough space
  char *result = (char *)malloc(result_capacity);
  if (result == NULL) {
    perror("Failed to allocate memory for result");
    return NULL;
  }

  const char *pos = source; // Pointer to current position in the source string
  char *current_pos =
      result; // Pointer to the current position in the result string

  while ((pos = strstr(pos, search)) != NULL) {
    // Copy the part before the match
    size_t bytes_to_copy = pos - source;
    while (result_capacity <=
           (current_pos - result) + bytes_to_copy + replacement_len + 1) {
      // Resize result if needed
      result_capacity *= 2; // Double the size
      result = (char *)realloc(result, result_capacity);
      if (result == NULL) {
        perror("Failed to reallocate memory for result");
        return NULL;
      }
      current_pos =
          result + (current_pos -
                    result); // Adjust current_pos to the new memory location
    }
    strncpy(current_pos, source, bytes_to_copy);
    current_pos += bytes_to_copy;

    // Copy the replacement string
    strcpy(current_pos, replacement);
    current_pos += replacement_len;

    // Move past the match in the source string
    pos += search_len; // Move past the current match
    source = pos;      // Update source to continue searching
  }

  // Copy any remaining part of the source string
  strcpy(current_pos, source);

  return result;
}
SHARED_LIB void flush() { fflush(stdout); }

#ifdef __cplusplus
}
#endif