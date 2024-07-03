# cafe-digital-geocaching

for the pi use docker container kreuterkeule/token-server-da-container:arm
for x86 systems use kreuterkeule/token-server-da-container:env or :v4 or :latest

## configuration
when starting docker container env variables need to be set (username, password) for generating tokens:

```sh
docker run -d -p 8080:8080 -e DEFAULT_USERNAME=admin -e DEFAULT_PASSWORD=1234 kreuterkeule/token-server-da-container:env --name token-server
```

those variables also need to be passed to the store of the challenges (./challanges/<challange-name>/src/store/index.js   change API_URL value)
the esp32 needs to be flashed with the same url in API_URL and wifi data, to connect to the internet
