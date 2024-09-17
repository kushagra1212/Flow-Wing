#!/bin/bash

# Stop and remove containers and volumes defined in docker-compose.yml
# docker-compose down -v
# docker-compose down repl-test

# Build and run containers defined in docker-compose.yml


docker-compose build  repl-test


# Run tests
docker-compose run --rm repl-test bash 
