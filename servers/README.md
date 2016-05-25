# Servers

### Manual TCP Requests
```
# better method
echo "GET / HTTP/1.1" | nc example.com 80

# worse method
telnet example.com 80
> GET / HTTP/1.1
```

### Manual TLS Requests
```
RESOURCE='index.html'

(printf 'GET '${RESOURCE}' HTTP/1.1\r\nHost: webkeks.org\r\n\r\n'; cat) | openssl s_client -connect webkeks.org:443
# cat is just to force openssl to send the HTTP request
```
