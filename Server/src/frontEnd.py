import requests, json
# r = requests.get('https://api.github.com/user', auth=('user', 'pass'))
# r.status_code
# # 200
# r.headers['content-type']
# # 'application/json; charset=utf8'
# r.encoding
# # 'utf-8'
# r.text
# # '{"type":"User"...'
# r.json()
# # {'disk_usage': 368627, 'private_gists': 484, ...}

with requests.Session() as s:
    r = s.get('http://localhost:8080/', params=b'params', data=b'data', json=['json'], headers={'header key': 'header value'}, allow_redirects=False)
    print(f"status: {r.status_code}\nheader: {r.headers}\ntext: {r.text}\n") # json: {r.json()}\n

# url – URL for the new Request object.
# params – (optional) Dictionary, list of tuples or bytes to send in the query string for the Request.
# data – (optional) Dictionary, list of tuples, bytes, or file-like object to send in the body of the Request.
# json – (optional) A JSON serializable Python object to send in the body of the Request.
# headers – (optional) Dictionary of HTTP Headers to send with the Request.
# cookies – (optional) Dict or CookieJar object to send with the Request.
# files – (optional) Dictionary of 'name': file-like-objects (or {'name': file-tuple}) for multipart encoding upload. file-tuple can be a 2-tuple ('filename', fileobj), 3-tuple ('filename', fileobj, 'content_type') or a 4-tuple ('filename', fileobj, 'content_type', custom_headers), where 'content-type' is a string defining the content type of the given file and custom_headers a dict-like object containing additional headers to add for the file.
# auth – (optional) Auth tuple to enable Basic/Digest/Custom HTTP Auth.
# timeout (float or tuple) – (optional) How many seconds to wait for the server to send data before giving up, as a float, or a (connect timeout, read timeout) tuple.
# allow_redirects (bool) – (optional) Boolean. Enable/disable GET/OPTIONS/POST/PUT/PATCH/DELETE/HEAD redirection. Defaults to True.
# proxies – (optional) Dictionary mapping protocol to the URL of the proxy.
# verify – (optional) Either a boolean, in which case it controls whether we verify the server’s TLS certificate, or a string, in which case it must be a path to a CA bundle to use. Defaults to True.
# stream – (optional) if False, the response content will be immediately downloaded.
# cert – (optional) if String, path to ssl client cert file (.pem). If Tuple, (‘cert’, ‘key’) pair.