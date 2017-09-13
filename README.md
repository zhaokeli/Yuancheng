# 远程桌面管理工具
本软件使用 **c++** **duilib**开发<br>
博客 <a href="http://www.zhaokeli.com" target="_blank">http://www.zhaokeli.com</a>
`
if (!in_array($domain, ['hm.loc', 'hm.hm'])) {
    //指定下面用户组在外网可以打开
    if (!in_array(USER_GROUP_ID, [2, 3, 4, 6, 7, 8, 9, 10, 11, 12])) {
        //其它用户组在外网使用域名访问
        $okip  = cache('access_ip');
        $usage = [
            'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.16 Safari/537.36',
            'Mozilla/5.0 (Linux; zh-cn;) WebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1 hemei/1.0',
            'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.1650.16 Safari/537.36 tencenttraveler/1.0',
        ];
        $usage = array_map('strtolower', $usage);
        $usa   = strtolower($_SERVER['HTTP_USER_AGENT']);
        $ip    = get_client_ip();
        // if (!in_array($ip, $okip) || !in_array($usa, $usage)) {
        if (!in_array($usa, $usage)) {
            die();
        }
    }
}
`
