#!/bin/bash

# Stop and remove containers and volumes defined in docker-compose.yml
docker-compose down -v
docker-compose down --remove-orphans

# Build and run containers defined in docker-compose.yml


docker-compose up repl-dev -d  --build 


# Run Repl Dev
docker-compose run --rm repl-dev /bin/bash
 

