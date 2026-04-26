---
sidebar_position: 8
---

import CodeBlock from "../../src/components/common/CodeBlock";
import Toast from "../../src/components/common/Toast";

# Creating an Server

## Overview

This documentation provides an example of how to create an HTTP server in Flow-Wing using the `Vortex` module. The server handles various HTTP requests, including GET and POST methods, and responds with appropriate content, including HTML and JSON.

## Modules Required

To create the HTTP server, you will need to bring in the following modules:

- `Vortex`: For handling HTTP requests and responses.
- `File`: For reading files from the filesystem.
- `Err`: For error handling.
- `Json`: For parsing JSON data.
- `Map`: For storing key-value pairs.

## Example Code

Here is the complete example of a simple HTTP server that serves a home page and handles JSON requests:

<CodeBlock code={
`bring Vortex
bring File
bring Err
bring Json
bring Map

fun handleHomePage(req: Vortex::HttpRequest, res: Vortex::HttpResponse) -> nthg {
  var homePage: str, homePageLoadErr: Err::Result = File::read("homePage.html", "r")    
  /; Handle GET request for the home page

  if (homePageLoadErr != Nir) {
    print(homePageLoadErr.getMessage(), "\\n")
    res.send({
      status: 500,
      content_type: "text/html",
      body: \`
      <html>
        <body>
          <h1>Error Loading Home Page</h1>
        </body>
      </html>
      \`
    })
    return :
  }
  
  var err: Err::Result = res.send({
    status: 200,
    content_type: "text/html",
    body: homePage
  })
  
  if err != Nir {
    print("Error sending response: ", err.getMessage(), "\\n")
  }
}

fun handleGet(req: Vortex::HttpRequest, res: Vortex::HttpResponse) -> nthg {
  var err: Err::Result = res.send({
    status: 200,
    content_type: "application/json",
    body: \`{
      "message": "Welcome to the Flow-Wing Programming Language!"
    }\`
  })
  
  if err != Nir {
    print("Error sending response: ", err.getMessage(), "\\n")
  }
}

fun handlePost(req: Vortex::HttpRequest, res: Vortex::HttpResponse) -> nthg {
  const body: Map::String = Json::parseObject(req.body)
  var name: str = body.get("name")
  
  var err: Err::Result = res.send({
    status: 200,
    content_type: "application/json",
    body: \`
       {
         "message": "Welcome to the Flow-Wing Programming Language!",
         "body": \` + body.get("name") + \`
       }
       \`
  })
}

const port: int = 8080
print("Flow-Wing server starting on port: ", port, "\\n")
var server: Vortex::Server = new Vortex::Server(port)
server.setRoute("GET", "/", handleHomePage)
server.setRoute("GET", "/api/welcome", handleGet)
server.setRoute("POST", "/", handlePost)
server.start()
`} language="fg"/>


### Starting the Server:

<CodeBlock code={
`FlowWing --F=main.fg -O=-O3 --server
`} />

<Toast message="Do not forget to use the --server flag" title="Server Started" type="warning"/>


<iframe
  width="800"
  height="400"
  src="https://github.com/user-attachments/assets/4d7502a9-e1de-4c20-a82b-4ffee80df2b9"
  title="YouTube video player"
  frameborder="0"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen
></iframe>

## Explanation of Functions

### `handleHomePage`

- This function handles GET requests to the home page (`/`).
- It attempts to read `homePage.html`. If successful, it sends the content with a 200 status code; otherwise, it sends a 500 error response.

### `handleGet`

- This function handles GET requests to the `/api/welcome` endpoint.
- It responds with a JSON message welcoming users to the Flow-Wing programming language.

### `handlePost`

- This function handles POST requests to the home page (`/`).
- It parses the JSON body of the request to extract the `name` field and responds with a JSON message that includes the name.

## Starting the Server

- The server is initialized on port 8080.
- Routes are defined for handling specific paths and HTTP methods.
- The server starts listening for incoming requests.

## Conclusion

This example demonstrates how to create a basic HTTP server in Flow-Wing using the `Vortex` module. You can expand upon this foundation to handle more complex routing and request processing as needed.
