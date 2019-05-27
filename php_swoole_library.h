/**
 * Generated by build-library.php, Please DO NOT modify!
 */

static const char* swoole_lib_source_array =
    "function swoole_array_walk(array &$array, callable $callback, $userdata = null): bool\n"
    "{\n"
    "    foreach ($array as $key => &$item) {\n"
    "        $callback($item, $key, $userdata);\n"
    "    }\n"
    "    return true;\n"
    "}\n"
    "\n"
    "function swoole_array_walk_recursive(array &$array, callable $callback, $userdata = null): bool\n"
    "{\n"
    "    foreach ($array as $key => &$item) {\n"
    "        if (is_array($item)) {\n"
    "            swoole_array_walk_recursive($item, $callback, $userdata);\n"
    "        } else {\n"
    "            $callback($item, $key, $userdata);\n"
    "        }\n"
    "    }\n"
    "    return true;\n"
    "}";

static const char* swoole_lib_source_curl =
    "class swoole_curl_handler\n"
    "{\n"
    "    /** @var Swoole\\Coroutine\\Http\\Client */\n"
    "    private $client;\n"
    "    private $info;\n"
    "    private $outputStream;\n"
    "\n"
    "    /** @var callable */\n"
    "    private $headerFunction;\n"
    "    /** @var callable */\n"
    "    private $readFunction;\n"
    "    /** @var callable */\n"
    "    private $writeFunction;\n"
    "    /** @var callable */\n"
    "    private $progressFunction;\n"
    "\n"
    "    public $returnTransfer = true;\n"
    "    public $method = 'GET';\n"
    "    public $headers = [];\n"
    "\n"
    "    function create(string $url)\n"
    "    {\n"
    "        $info = parse_url($url);\n"
    "        $ssl = $info['scheme'] === 'https';\n"
    "        if (empty($info['port'])) {\n"
    "            $port = $ssl ? 443 : 80;\n"
    "        } else {\n"
    "            $port = intval($info['port']);\n"
    "        }\n"
    "        $this->info = $info;\n"
    "        $this->client = new Swoole\\Coroutine\\Http\\Client($info['host'], $port, $ssl);\n"
    "    }\n"
    "\n"
    "    function execute()\n"
    "    {\n"
    "        $client = $this->client;\n"
    "        $client->setMethod($this->method);\n"
    "        if ($this->headers) {\n"
    "            $client->setHeaders($this->headers);\n"
    "        }\n"
    "        if (!$client->execute($this->getUrl())) {\n"
    "            return false;\n"
    "        }\n"
    "\n"
    "        if ($client->headers and $this->headerFunction) {\n"
    "            $cb = $this->headerFunction;\n"
    "            if ($client->statusCode === 200) {\n"
    "                $cb($this, \"HTTP/1.1 200 OK\\r\\n\");\n"
    "            }\n"
    "            foreach ($client->headers as $k => $v) {\n"
    "                $cb($this, \"$k: $v\\r\\n\");\n"
    "            }\n"
    "            $cb($this, '');\n"
    "        }\n"
    "\n"
    "        if ($client->body and $this->readFunction) {\n"
    "            $cb = $this->readFunction;\n"
    "            $cb($this, $this->outputStream, strlen($client->body));\n"
    "        }\n"
    "\n"
    "        if ($this->returnTransfer) {\n"
    "            return $client->body;\n"
    "        } else {\n"
    "            if ($this->outputStream) {\n"
    "                return fwrite($this->outputStream, $client->body) === strlen($client->body);\n"
    "            } else {\n"
    "                echo $this->outputStream;\n"
    "            }\n"
    "            return true;\n"
    "        }\n"
    "    }\n"
    "\n"
    "    function close(): void\n"
    "    {\n"
    "        $this->client = null;\n"
    "    }\n"
    "\n"
    "    function getErrorCode(): int\n"
    "    {\n"
    "        return $this->client->errCode;\n"
    "    }\n"
    "\n"
    "    function getErrorMsg(): string\n"
    "    {\n"
    "        return $this->client->errMsg;\n"
    "    }\n"
    "\n"
    "    private function getUrl(): string\n"
    "    {\n"
    "        if (empty($this->info['path'])) {\n"
    "            $url = '/';\n"
    "        } else {\n"
    "            $url = $this->info['path'];\n"
    "        }\n"
    "        if (!empty($this->info['query'])) {\n"
    "            $url .= '?' . $this->info['query'];\n"
    "        }\n"
    "        if (!empty($this->info['query'])) {\n"
    "            $url .= '#' . $this->info['fragment'];\n"
    "        }\n"
    "        return $url;\n"
    "    }\n"
    "\n"
    "    function setOption(int $opt, $value): bool\n"
    "    {\n"
    "        switch ($opt) {\n"
    "            case CURLOPT_URL:\n"
    "                $this->create($value);\n"
    "                break;\n"
    "            case CURLOPT_RETURNTRANSFER:\n"
    "                $this->returnTransfer = $value;\n"
    "                break;\n"
    "            case CURLOPT_ENCODING:\n"
    "                if (empty($value)) {\n"
    "                    $value = 'gzip';\n"
    "                }\n"
    "                $this->headers['Accept-Encoding'] = $value;\n"
    "                break;\n"
    "            case CURLOPT_POST:\n"
    "                $this->method = 'POST';\n"
    "                break;\n"
    "            case CURLOPT_HTTPHEADER:\n"
    "                foreach ($value as $header) {\n"
    "                    list($k, $v) = explode(':', $header);\n"
    "                    $v = trim($v);\n"
    "                    if ($v) {\n"
    "                        $this->headers[$k] = $v;\n"
    "                    }\n"
    "                }\n"
    "                break;\n"
    "            case CURLOPT_CUSTOMREQUEST:\n"
    "                break;\n"
    "            case CURLOPT_PROTOCOLS:\n"
    "                if ($value > 3) {\n"
    "                    throw new swoole_curl_exception(\"option[{$opt}={$value}] not supported\");\n"
    "                }\n"
    "                break;\n"
    "            case CURLOPT_HTTP_VERSION:\n"
    "                break;\n"
    "            case CURLOPT_SSL_VERIFYHOST:\n"
    "                break;\n"
    "            case CURLOPT_SSL_VERIFYPEER:\n"
    "                $this->client->set(['ssl_verify_peer' => $value]);\n"
    "                break;\n"
    "            case CURLOPT_CONNECTTIMEOUT:\n"
    "                $this->client->set(['connect_timeout' => $value]);\n"
    "                break;\n"
    "            case CURLOPT_FILE:\n"
    "                $this->outputStream = $value;\n"
    "                break;\n"
    "            case CURLOPT_HEADER:\n"
    "                break;\n"
    "            case CURLOPT_HEADERFUNCTION:\n"
    "                $this->headerFunction = $value;\n"
    "                break;\n"
    "            case CURLOPT_READFUNCTION:\n"
    "                $this->readFunction = $value;\n"
    "                break;\n"
    "            case CURLOPT_WRITEFUNCTION:\n"
    "                $this->writeFunction = $value;\n"
    "                break;\n"
    "            case CURLOPT_PROGRESSFUNCTION:\n"
    "                $this->progressFunction = $value;\n"
    "                break;\n"
    "            default:\n"
    "                throw new swoole_curl_exception(\"option[{$opt}] not supported\");\n"
    "        }\n"
    "        return true;\n"
    "    }\n"
    "\n"
    "    function reset(): void\n"
    "    {\n"
    "        $this->client->body = '';\n"
    "    }\n"
    "}\n"
    "\n"
    "class swoole_curl_exception extends swoole_exception\n"
    "{\n"
    "\n"
    "}\n"
    "\n"
    "function swoole_curl_init(): swoole_curl_handler\n"
    "{\n"
    "    return new swoole_curl_handler();\n"
    "}\n"
    "\n"
    "function swoole_curl_setopt(swoole_curl_handler $obj, $opt, $value): bool\n"
    "{\n"
    "    return $obj->setOption($opt, $value);\n"
    "}\n"
    "\n"
    "function swoole_curl_setopt_array(swoole_curl_handler $obj, $array): bool\n"
    "{\n"
    "    foreach ($array as $k => $v) {\n"
    "        if ($obj->setOption($k, $v) === false) {\n"
    "            return false;\n"
    "        }\n"
    "    }\n"
    "    return true;\n"
    "}\n"
    "\n"
    "function swoole_curl_exec(swoole_curl_handler $obj)\n"
    "{\n"
    "    return $obj->execute();\n"
    "}\n"
    "\n"
    "function swoole_curl_close(swoole_curl_handler $obj): void\n"
    "{\n"
    "    $obj->close();\n"
    "}\n"
    "\n"
    "function swoole_curl_error(swoole_curl_handler $obj): string\n"
    "{\n"
    "    return $obj->getErrorMsg();\n"
    "}\n"
    "\n"
    "function swoole_curl_errno(swoole_curl_handler $obj): int\n"
    "{\n"
    "    return $obj->getErrorCode();\n"
    "}\n"
    "\n"
    "function swoole_curl_reset(swoole_curl_handler $obj): void\n"
    "{\n"
    "    $obj->reset();\n"
    "}";

static const char* swoole_lib_source_waitgroup =
    "namespace Swoole\\Coroutine;\n"
    "\n"
    "class WaitGroup\n"
    "{\n"
    "    private $count = 0;\n"
    "    private $chan;\n"
    "\n"
    "    public function __construct()\n"
    "    {\n"
    "        $this->chan = new Channel();\n"
    "    }\n"
    "\n"
    "    public function add()\n"
    "    {\n"
    "        $this->count++;\n"
    "    }\n"
    "\n"
    "    public function done()\n"
    "    {\n"
    "        $this->chan->push(true);\n"
    "    }\n"
    "\n"
    "    public function wait()\n"
    "    {\n"
    "        while ($this->count--) {\n"
    "            $this->chan->pop();\n"
    "        }\n"
    "    }\n"
    "\n"
    "}";

static const char* swoole_lib_source_constant =
    "define('SWOOLE_LIBRARY', true);\n"
    "class_alias('Swoole\\Coroutine\\WaitGroup', 'Co\\WaitGroup', false);";


static void swoole_load_library()
{
    zend::eval(swoole_lib_source_array, "@swoole/library/array.php");
    zend::eval(swoole_lib_source_curl, "@swoole/library/curl.php");
    zend::eval(swoole_lib_source_waitgroup, "@swoole/library/waitgroup.php");
    zend::eval(swoole_lib_source_constant, "@swoole/library/constant.php");
}