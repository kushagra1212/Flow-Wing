#!/bin/bash

# Stop and remove containers and volumes defined in docker-compose.yml
# docker-compose down -v
# docker-compose down --remove-orphans

# Build and run containers defined in docker-compose.yml


docker-compose up compiler-dev -d --build 


# Run Compiler Dev
docker-compose run --rm compiler-dev /bin/bash
 

