# redis

## Redis是一个key-value存储统

### 存储的value类型

- 括string、list、set、zset(有序集合)和hash

### 他与之前的Mysql数据库不一样,是新型数据库类型NoSql类型(不支持sql)

### 为什么使用Redis?

- 可以用来做数据库,缓存,消息中间件.

### 数据库

- Redis本质就是数据库，内存空间是有限的,不能像硬盘那么大，所以多数场景都是关系型数据库,和Redis缓存的方式运行Redis.

	- 内存，比磁盘快

### 缓存

- mysql并发几百就会扛不住，为了支持更高的并发，会使用缓存为数据库建筑一道屏障，大多数请求在缓存这层完成

	- redis是把数据存储到内存中，访问速度快，很适合缓存

### 消息中间件

- Redis支持发布/订阅消息，一般不使用它,他不是强项.MQ Rabbit Rocket

### redis特性

- Redis支持数据的持久化，可以将内存中的数据保存在磁盘中，重启的时候可以再次加载进行使用。
- Redis不仅仅支持简单的key-value类型的数据，同时还提供list,set, zset,hash等数据结构的存储。
- Redis支持数据的备份，即master-slave模式的数据备份。保证服务器稳定，主机坏了从机顶上

### 优势

- 性能极高-Redis能读的速度是110000次/s,写的速度是81000次/s。
- 丰富的数据类型-Redis支持二进制案例的Strings, Lists, Hashes, Sets 及 Ordered Sets数据类型操作。
- 原子- Redis的所有操作都是原子性的，同时Redis还支持对几个操作全并后的原子性执行。
- 丰富的特性– Redis还支持publish/subscribe,通知, key过期等等特性。
- redis应用场景用来做缓存(ehcache/memcached)——redis的所有数据是放在内存中的(内存数据库)可以在某些特定应用场景下替代传统数据库———比如社交类的应用
- 在一些大型系统中，巧妙地实现一些特定的功能: session共享、购物车
- 单线程，多进程，没有资源冲突的问题，副本拷出去给其他进程使用，不会影响本机

## hiredis库使用

### 1 连接redis数据库

- 1.1 无超时时间，阻塞

	- redisContext *redisConnect(const char *ip, int port); 返回一个上下文切换对象

- 1.2 设置超时时间，阻塞

	- redisContext *redisConnectWithTimeout(const char *ip, int port, const struct timeval tv);  

- 1.3 非阻塞，立刻返回，也就无所谓超时

	- redisContext *redisConnectNonBlock(const char *ip, int port);

### 2 执行命令

- void *redisCommand(redisContext *c, const char *format, ...);
- 2.1 返回值

	- 返回值是redisReply类型的指针

	  /* This is the reply object returned by redisCommand() */
	  typedef struct redisReply {
	     int type; /* REDIS_REPLY_* */
	     PORT_LONGLONG integer; /* The integer when type is REDIS_REPLY_INTEGER */
	     int len; /* Length of string */
	     char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
	     size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
	     struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
	  } redisReply;

- 2.2 返回值类型

	- #define REDIS_REPLY_STRING 1    //字符串
	- #define REDIS_REPLY_ARRAY 2     //数组，例如mget返回值
	- #define REDIS_REPLY_INTEGER 3   //数字类型
	- #define REDIS_REPLY_NIL 4       //空
	- #define REDIS_REPLY_STATUS 5    //状态，例如set成功返回的‘OK’
	- #define REDIS_REPLY_ERROR 6     //执行失败

### 3 基本命令，get，set -->string

- 3.1 set

	- redisReply *r1 = (redisReply*)redisCommand(c, "set k v");

		- 结果： type = 5，len = 2，str = OK
返回的类型5，是状态。str是OK，代表执行成功。

- 3.2 get

	- redisReply *r2 = (redisReply*)redisCommand(c, "get k");

		- 结果： type = 1，len = 1，str = v
返回的类型是1，字符串类型，str是‘v’ ，刚才保存的

### 4 存取二进制

- char sz[] = { 0,1,2,3,0 };
redisReply *r3 = (redisReply*)redisCommand(c, "set kb %b",sz,sizeof(sz));

	- 存二进制的时候，使用%b，后面需要对应两个参数，指针和长度。

- redisReply *r4 = (redisReply*)redisCommand(c, "get kb");

	- 读取二进制的时候，和普通是一样的，str字段是地址，len字段是长度。

## SDS简单动态字符串

### 键值对在底层就是由SDS实现的

### SDS也有一个表头（header）用来存放sds的信息

struct sdshdr { 
 int len; //buf中已占用空间的长度 
 int free; //buf中剩余可用空间的长度 
 char buf[]; //初始化sds分配的数据空间，而且是柔性数组（Flexible array member） 
};

### SDS本质上就是char *，因为有了表头sdshdr结构的存在，所以SDS比传统C字符串在某些方面更加优秀，并且能够兼容传统C字符串。

### 3.1因为SDS兼容传统的C字符串，采用以’\0’作为结尾，所以SDS就能够使用一部分

###  3.2二进制安全（Binary Safe）

- 因为传统C字符串符合ASCII编码，这种编码的操作的特点就是：遇零则止 。如果传统字符串保存图片，视频等二进制文件，操作文件时就被截断了。
- 而SDS表头的buf被定义为字节数组，因为判断是否到达字符串结尾的依据则是表头的len成员，这意味着它可以存放任何二进制的数据和文本数据，包括’\0’

### 3.3 获得字符串长度的操作复杂度为O(1)

### 3.4 杜绝缓冲区溢出

- 因为SDS表头的free成员记录着buf字符数组中未使用空间的字节数，所以，在进行APPEND命令向字符串后追加字符串时，如果不够用会先进行内存扩展，在进行追加。

### 4.1 SDS内存分配策略—空间预分配

通过空间预分配策略，Redis可以减少连续执行字符串增长操作所需的内存重分配次数。

- 空间预分配策略用于优化SDS的字符串增长操作。
- 如果对SDS进行修改，SDS表头的len成员小于1MB，那么就会分配和len长度相同的未使用空间。free=len。
- 如果对SDS进行修改，SDS的长度大于等于1MB，那么就会分配1MB的未使用空间。

### 4.2 SDS内存释放策略—惰性空间释放

- 改变len、free值，下次添加直接覆盖，有点类似文件系统删除文件操作

### 采用容性数组

- 数组可变

## Redis源码剖析—链表结构

typedef struct listNode { 
 struct listNode *prev; //前驱节点，如果是list的头结点，则prev指向NULL 
 struct listNode *next;//后继节点，如果是list尾部结点，则next指向NULL 
 void *value; //万能指针，能够存放任何信息 
} listNode;

### redis还提供了一个表头，用于存放上面双向链表的信息，它由adlist.h/list结构表示：

typedef struct list { 
 listNode *head; //链表头结点指针 
 listNode *tail; //链表尾结点指针 
 //下面的三个函数指针就像类中的成员函数一样 
 void *(*dup)(void *ptr); //复制链表节点保存的值 
 void (*free)(void *ptr); //释放链表节点保存的值 
 int (*match)(void *ptr, void *key); //比较		链表节点所保存的节点值和另一个输入的值是否相等 
 unsigned long len; //链表长度计数器 
} list;

### 利用list表头管理链表信息的好处：

- head和tail指针：对于链表的头结点和尾结点操作的复杂度为O(1)。
- len 链表长度计数器：获取链表中节点数量的复杂度为O(1)。
- dup、free和match指针：实现多态，链表节点listNode使用万能指针void *保存节点的值，
- 而表头list使用dup、free和match指针来针对链表中存放的不同对象从而实现不同的方法。

### 迭代器的好处：

- 提供一种方法顺序访问一个聚合对象中各个元素, 而又不需暴露该对象的内部表示。
- • 将指针操作进行了统一封装，代码可读性增强。

## redis---字典结构

### redis的字典是由哈希表实现的，一个哈希表有多个节点，每个节点保存一个键值对。

- 字典，健值对，值可能也是字典

### redis结构体

typedef struct dictht { //哈希表 
 dictEntry **table; //存放一个数组的地址，数组存放着哈希表节点dictEntry的地址。 
 unsigned long size; //哈希表table的大小，初始化大小为4 
 unsigned long sizemask; //用于将哈希值映射到table的位置索引。它的值总是等于(size-1)。 
 unsigned long used; //记录哈希表已有的节点（键值对）数量。 
} dictht;

- redis中哈希表定义在dict.h/dictht中。

### 哈希表节点

typedef struct dictEntry { 
 void *key; //key 
 union { 
 void *val; 
 uint64_t u64; 
 int64_t s64; 
 double d; 
 } v; //value 
 struct dictEntry *next; //指向下一个hash节点，用来解决hash键冲突（collision） 
} dictEntry;

- 哈希表的table指向的数组存放这dictEntry类型的地址。也定义在dict.h/dictEntryt中。

### 一个字典默认两张哈希表

- 哈希表有不同成员的，有管理大小，还有数组

## Redis 整数集合(intset)

typedef struct intset { 
 		uint32_t encoding; //编码格式，有如下三种格式，初始值默认为INTSET_ENC_INT16 

 			uint32_t length; //集合元素数量 
 			int8_t contents[]; //保存元素的数组，元素类型并不一定是ini8_t类型，柔性数组不占intset结构体大小，并且数组中的元素从小到大排列。 
} intset; //整数集合结构

### 整数集合（intset）是集合键底层实现之一。集合键另一实现是值为空的散列（hashtable），散列表比较浪费空间

### 在redis集合键命令：redis集合键命令详解

- 127.0.0.1:6379> SADD set1 1 2 3

	- (integer) 3

- 127.0.0.1:6379> SADD set1 1

	- (integer) 0

- 127.0.0.1:6379> SMEMBERS set1

	- 1) "1"，2) "2"，3) "3"

- 127.0.0.1:6379> SISMEMBER set1 2 //查看是否存在
- 127.0.0.1:6379> SREM set1 1    //删除

### 编码格式，有如下三种格式，初始值默认为INTSET_ENC_INT16，目的是节省空间

- 如果添加的数字位数大于16位那么，对集合升级，判断数字在那个位数范围内，重新分配空间

## redis---跳跃表

### 有序数组 : 插入数据 有序 , 二分 logN 但是 插入导致的调整要后移 o(N) --> o(N)
有序链表(单链表 -- 单向) : 插入 遍历找到位置 o(N) 操作o(1) --> o(N) 问题: 定位麻烦

### 单向链表没法二分查找, 但是我们可以来一些索引, 举例子来说可以使用奇数的节点作为索引比如 8个元素 一级索引4个点 二级索引 2个点 创建索引的思路 可以是每一层索引都是上一层元素个数的一半

### 可以建立多层索引, 来确定数据应该在什么范围, 直到索引项小于2，查找 支持 平均o( logn )最坏 o(n)复杂度的节点查找 , 还可以通过顺序性, 批量处理节点

### 定义·：跳跃表是一个有序链表，其中每个节点包含不定数量的链接，节点中的第i个链接构成的单向链表跳过含有少
于i个链接的节点。

### 跳跃表支持平均O(logN)，最坏O(N)复杂度的节点查找，大部分情况下，跳跃表的效率可以和平衡树相媲美

### 跳跃表在redis中当数据较多时作为有序集合键的实现方式之一

- 在redis中实现有序集合的办法是：跳跃表+哈希表

### 排行榜：可以使用跳跃表加哈希

### typedef struct zskiplistNode {
             struct zskiplistLevel {
             struct zskiplistNode *forward;// 前进指针
             unsigned int span;// 跨度
              } level[]; // 层 -- 索引
            struct zskiplistNode *backward; // 后退指针
            double score; // 分值
            robj *obj;// 成员对象
} zskiplistNode;

- 成员对象：指向sds，是一个字符串对象
- 在跳跃表中，节点按各自所保存的分值从小到大排列，分值是成员对象里面的某个值，比如id，年龄什么的
- 每个层都带有两个属性：前进指针和跨度。

	- 跨度则记录了前进指针所指向节点和当前节点的距离。
	- 跨度是用来计算排位的.

- 跳跃表节点的level数组可以包含多个元素，每个元素都包含一个指向其他节点的指针，程序可以通过这些层来加快访问其他节点的速度，一般来说，层的数量越多，访问其他节点的速度就越快
- 每次创建一个新跳跃表节点的时候，程序都根据幂次定律（power law,越大的数出现的概率越小）随机生成一个介于1和32之间的值作为level数组的大小，这个大小就是层的“高度”。

### typedef struct zskiplist {
            struct zskiplistNode *header, *tail;// 表头节点和表尾节点
            unsigned long length; // 表中节点的数量
            int level; // 表中层数最大的节点的层数
} zskiplist;

### 索引维护

- 首先了解创建层的机制
int zslRandomLevel(void) {
         int level = 1;
         while ((random()&0xFFFF) < (ZSKIPLIST_P * 0xFFFF)) // ZSKIPLIST_P 0.25
         level += 1;
         return (level<ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL; // 最大32级 } // 插入节点时, 该节点作为1-k 级索引, 需要随机来确认

	- 也就是说 采用的是随机数来确认 , 决定是否将单个节点放置到下一层概率是0.25
	- 接下来根据level数, 根据节点分数 , 添加节点( 首先找到位置, 然后连接 , 不同层都要操作 )
	- 删除节点, 就是直接根据分数定位节点, 然后删除
	- 分一级概率减小

## 压缩列表

### redis 3.2以后，quicklist作为列表键的实现底层实现之一，代替了压缩列表。

### 压缩列表(ziplist)是哈希键的底层实现之一。它是经过特殊编码的双向链表，和整数集合(intset)一样，是为了提高内存的存储效率而设计的。当保存的对象是小整数值，或者是长度较短的字符串，那么redis就会使用压缩列表来作为哈希键的实现。val

### 子主题 3

- zlbytes：占4个字节，记录整个压缩列表占用的内存字节数。 总字节数
- zltail_offset：占4个字节，记录压缩列表尾节点entryN距离压缩列表的起始地址的字节数。
- zllength：占2个字节，记录了压缩列表的节点数量。
- entry[1-N]：长度不定，保存数据。
- zlend：占1个字节，保存一个常数255(0xFF)，标记压缩列表的末端。

### entry 节点内部的结构在redis中，并没有定义结构体来进行操作，也是定义了一些宏

- prev_entry_len：记录前驱节点的长度。
- encoding：记录当前节点的value成员的数据类型以及长度。
- value：根据encoding来保存字节数组或整数。

### 子主题 5

- 里面数据节点类型，是用编码区分的

## 快速列表

### quicklist结构是在redis 3.2版本中新加的数据结构，用在列表的底层实现。

### 压缩列表ziplist结构本身就是一个连续的内存块，由表头、若干个entry节点和压缩列表尾部标识符zlend组成，通过一系列编码规则，提高内存的利用率，使用于存储整数和短字符串。
压缩列表ziplist结构的缺点是：每次插入或删除一个元素时，都需要进行频繁的调用realloc()函数进行内存的扩展或减小，然后进行数据”搬移”，甚至可能引发连锁更新，造成严重效率的损失。

## 数据类型

### 子主题 1

- 有序集合就是跳表和哈希表联合实现的，定位哈希，找范围跳表
- string——适合最简单的k-v存储，类似于memcached的存储结构，短信验证码，配置信息等，就用这种类型来存储。
- hash——一般key为ID或者唯一标示，value对应的就是详情了。如商品详情，个人信息详情，新闻详情等。
- list——因为list是有序的，比较适合存储一些有序且数据相对固定的数据。如省市区表、字典表等。因为list是有序的，适合根据写入的时间来排序，如：最新的***，消息队列等。
- set——可以简单的理解为ID-List的模式，如微博中一个人有哪些好友，set最牛的地方在于，可以对两个set提供交集、并集、差集操作。例如：查找两个人共同的好友等。
- Sorted Set——是set的增强版本，增加了一个score参数，自动会根据score的值进行排序。比较适合类似于top 10等不根据插入的时间来排序的数据。

## redis对象

### Redis---字符串命令实现(t_string)

- 子主题 1

	- OBJ_ENCODING_RAW 简单动态字符串实现的字符串对象 SDS，容性数组

### Redis---列表命令实现(t_list)

- quicklist本质上就是以ziplist为节点的双向链表 , redis3.2 以上的版本 , 列表采用quicklist来实现列表对象.

### Redis---哈希键命令实现(t_hash)

- 压缩列表中的entry节点，两两组成一个键值对。
/* redis.conf文件中的阈值 */ 
hash-max-ziplist-value 64 // ziplist中最大能存放的值长度 
hash-max-ziplist-entries 512 // ziplist中最多能存放的entry节点数量

	- 子主题 1

		- 如果这个哈希对象所存储的键值对或者ziplist的长度超过配置的限制，则会转换为字典结构，这写阈值条件上面已经列出，
而为了说明编码为 OBJ_ENCODING_HT 类型的哈希对象，我们仍用上面的 user:info 对象来表示一个字典结构的哈希对象，
哈希对象中的键值对都是字符串类型的对象。

### Redis---集合键命令实现(t_set)

- 如果set对象存储的是整型, 那么采用整型集合 intset实现集合对象

	- 如果set对象存储的非整型数据 , 如字符串等标签, 那么采用字典结构(hash table -- HT)实现集合对象

### Redis---有序集合键命令实现(t_zset)

- 在redis中实现有序集合的办法是：跳跃表+哈希表

	- . 跳跃表元素有序，而且可以范围查找，且实现起来比平衡树简单。
	- 2. 哈希表查找单个key时间复杂度性能高。

- 编码—encoding 对象—ptr
OBJ_ENCODING_SKIPLIST 跳跃表和字典实现的有序集合对象
OBJ_ENCODING_ZIPLIST 压缩列表实现的有序集合对象
- 我们创建一个视频播放量的有序集合，有体育sport、卡通carton、电视剧telepaly这三个成员                                        #define OBJ_ZSET_MAX_ZIPLIST_ENTRIES 128 // ziplist中最多存放的节点数 
#define OBJ_ZSET_MAX_ZIPLIST_VALUE 64 // ziplist中最大存放的数据长度

	- 当超过压缩列表的阈值时, 有序集合采用跳跃表+ 字典结构(hash表)的结构来实现

		- 查找单个用哈希表快速定位，查找元素第几位用跳表

- 子主题 4

## redis通知

### 通知功能介绍

- 客户端可以通过 订阅与发布功能（pub/sub）功能，来接收那些以某种方式改动了Redis数据集的事件。
目前Redis的订阅与发布功能采用的是发送即忘（fire and forget）的策略，当订阅事件的客户端断线时，它会丢失所有在断线期间分发给它的事件。

### 通知的类型

- 键空间通知（key-space notification）
- 键事件通知（key-event notification）
- 事件1 发送变化 --> 自动去通知事件2 (观察者模式)

### 消息通知

- 任务队列

	- 任务队列：顾名思义，就是“传递消息的队列”。与任务队列进行交互的实体有两类，一类是生产者（producer），另一类则是消费者（consumer）。生产者将需要处理的任务放入任务队列中，而消费者则不断地从任务独立中读入任务信息并执行。
	- 任务队列的好处

		- 松耦合。生产者和消费者只需按照约定的任务描述格式，进行编写代码。
易于扩展。多消费者模式下，消费者可以分布在多个不同的服务器中，由此降低单台服务器的负载。

	-  Redis实现任务队列

		- 使用Redis实现任务队列首先想到的就是Redis的列表类型，因为在Redis内部，==列表类型是由双向链表实现==的。
实现任务队列，只需让生产者将任务使用LPUSH加入到某个键中，然后另一个消费者不断地使用RPOP命令从该键中取出任务即可。

		  //生产者只需将task LPUSH到队列中 
		  127.0.0.1:6379> LPUSH queue task 
		  (integer) 1 
		  127.0.0.1:6379> LRANGE queue 0 -1 
		  1) "task" 
		  //消费者只需从队列中LPOP任务，如果为空则轮询。 
		  127.0.0.1:6379> LPOP queue 
		  "task" 
		  BLPOP指令可以在队列为空时处于阻塞状态。就不用处于轮询的状态。 
		  127.0.0.1:6379> BLPOP queue 0 //0表示无限制等待

-  优先级队列

	- 当一个队列中有许多任务仍然没有来得及被消费者及时消费时，如果出现紧急的消息，则不得不等待队列中的任务被一一取出，因此，需要实现一个优先级队列，当优先级队列不为空时，消费者优先取出优先级队列中的任务去执行。

	  //当两个键都有元素时，按照从左到右的顺序取第一个键中的一个元素 
	  127.0.0.1:6379> BRPOP queue1 queue2 0 
	  1) "queue1" 
	  2) "first" 
	  127.0.0.1:6379> BRPOP queue1 queue2 0 
	  1) "queue2" 
	  2) "second"

- 发布/订阅”模式

	- 发布/订阅”（publish/subscribe）模式同样可以实现进程间通信，==订阅者可以订阅一个或多个频道（channel），而发布者可以向指定的频道发送消息，所有订阅次频道的订阅者都会收到次消息。==

## 持久化

### Redis提供了两种持久化的机制：RDB和AOF

- RDB持久化是把当前进程数据生成时间点快照（point-in-time snapshot）保存到硬盘的过程，避免数据意外丢失。

	- 手动触发的两条命令

		- SAVE：阻塞当前Redis服务器，直到RDB过程完成为止。
		- BGSAVE：Redis 进程执行fork()操作创建出一个子进程，在后台完成RDB持久化的过程。（主流）

	- 自动触发的配置：

		- save 900 1 //服务器在900秒之内，对数据库执行了至少1次修改 
		- save 300 10 //服务器在300秒之内，对数据库执行了至少10修改 
		- save 60 1000 //服务器在60秒之内，对数据库执行了至少1000修改 
		- // 满足以上三个条件中的任意一个，则自动触发 BGSAVE 操作 
		- // 或者使用命令CONFIG SET 命令配置

	- RDB的优点：

		- RDB是一个紧凑压缩的二进制文件，代表Redis在某个时间点上的数据快照。非常适用于备份，全景复制等场景。
		- Redis 加载RDB恢复数据远远快于AOF的方式。
		- 1、只有一个文件 dump.rdb，方便持久化。
		- 2、容灾性好，一个文件可以保存到安全的磁盘。
		- 3、性能最大化，fork 子进程来完成写操作，让主进程继续处理命令，所以是 IO 最大化。使用单独子进程来进行持久化，主进程不会进行任何 IO 操作，保证了 redis 的高
		- 性能
		- 4.相对于数据特大时，比 AOF 的启动效率更高。

	- RDB的缺点：

		- RDB没有办法做到实时持久化或秒级持久化。因为BGSAVE每次运行的又要进行fork()的调用创建子进程，这属于重量级操作，频繁执行成本过高
		- RDB文件使用特定的二进制格式保存，Redis版本演进的过程中，有多个RDB版本，这导致版本兼容的问题。

- AOF持久化：以独立日志的方式记录每次写命令，重启时在重新执行AOF文件中的命令达到恢复数据的目的。

	- 由于Redis是单线程响应命令，所以每次写AOF文件都直接追加到硬盘中，那么写入的性能完全取决于硬盘的负载，所以Redis会将命令写入到缓冲区中，然后执行文件同步操作，再将缓冲区内容同步到磁盘中，这样就很好的保持了高性能。

		- 主进程执行命令，子进程将命令写到磁盘

	- 只要数据存在于缓冲区，那么就有丢失的危险，当缓冲区向磁盘写入，主进程又执行命令，数据就会丢失

		- 

	- AOF重写的方式

		- 进程内已经超时的数据不在写入文件。
		- 无效命令不在写入文件。
		- 多条写的命令合并成一个。
		- AOF总是记录数据库的最终状态的一个命令集。类似于物理中的位移与路程的关系，位移总是关心的是启动到终点距离，而不关心是如何从起点到达终点。

	- 触发机制

		- 手动触发：BGREWRITEAOF 命令。
		- 自动触发：根据redis.conf的两个参数确定触发的时机。
		- auto-aof-rewrite-percentage 100：当前AOF的文件空间(aof_current_size)和上一次重写后AOF文件空间(aof_base_size)的比值。
		- auto-aof-rewrite-min-size 64mb：表示运行AOF重写时文件最小的体积。
		- 自动触发时机 = (aof_current_size > auto-aof-rewrite-min-size && (aof_current_size - aof_base_size) / aof_base_size >= auto-aof-rewrite-percentage)

	-  AOF重写的实现

		- AOF重写操作有可能会长时间阻塞服务器主进程，因此会fork()一个子进程在后台进行重写，然后父进程就可以继续响应命令请求。虽然解决了阻塞问题，但是有产生了新问题：子
进程在重写期间，服务器还会处理新的命令请求，而这些命令可能会对数据库的状态进行更改，从而使当前的数据库状态和AOF重写之后保存的状态不一致。
		- 因此Redis设置了一个AOF重写缓冲区的结构

			- 重写缓冲区并不是一个大块的内存空间，而是一些内存块的链表，没个内存块的大小为10MB，这样就组成了一个重写缓冲区。

		- 因此当客户端发来命令时，会执行以下操作：

			- 执行客户端的命令。
			- 将执行后的写命令追加到AOF缓冲区（server.aof_buf）中。
			- 将执行后的写命令追加到AOF重写缓冲区（server.aof_rewrite_buf_blocks）中。
			- 这样以来就不会丢失子进程重写期间，父进程新处理的写命令了。

	- 而父进程是如何将差异数据发送给子进程呢？Redis中使用了管道技术。进程间通信(IPC)之管道详解
	- AOF文件的载入

		- 因为Redis命令总是在一个客户端中执行，因此，为了载入AOF文件，需要创建一个关闭监听套接字的伪客户端。

	- 优点：

		- 、数据安全，aof 持久化可以配置 appendfsync 属性，有 always，每进行一次 命令操作就记录到 aof 文件中一次。
		- 2、通过 append 模式写文件，即使中途服务器宕机，可以通过 redis-check-aof 工具解决数据一致性问题。
		- 3、AOF 机制的 rewrite 模式。AOF 文件没被 rewrite 之前（文件过大时会对命令 进行合并重写），可以删除其中的某些命令（比如误操作的 flushall）)

	- 缺点

		- 1、AOF 文件比 RDB 文件大，且恢复速度慢。
		- 2、数据集大的时候，比 rdb 启动效率低。

	- 优缺点是什么？

		- AOF文件比RDB更新频率高，优先使用AOF还原数据。
		- AOF比RDB更安全也更大
		- RDB性能比AOF好
		- 如果两个都配了优先加载AOF

## Redis---Redis数据库及相关命令实现(db)

### Redis是一个key-value数据库服务器，它将所有的键值对都保存在 redisDb 结构中的 dict 字典成员中（Redis 字典结构源码剖析）。

### 键的过期时间

- redisBb结构中的 expires 字典保存这设置了过期时间的键和过期的时间。通过 EXPIRE 、 PEXPIRE、 EXPIREAT 和 PEXPIREAT四个命令，客户端可以给某个存在的键设置过期时
间，当键的过期时间到达时，键就不再可用。

### 面试问题
Redis的过期键的删除策略

- 定时过期：每个设置过期时间的key都需要创建一个定时器，到过期时间就会立即清除。该策略可以立即清除过期的数据，对内存很友好；但是会占用大量的CPU资源去处理过期的数据，从而影响缓存的响应时间和吞吐量。
- 惰性过期：只有当访问一个key时，才会判断该key是否已过期，过期则清除。该策略可以最大化地节省CPU资源，却对内存非常不友好。极端情况可能出现大量的过期key没有再次被访问，从而不会被清除，占用大量内存。
- 定期过期：每隔一定的时间，会扫描一定数量的数据库的expires字典中一定数量的key，并清除其中已过期的key。该策略是前两者的一个折中方案。通过调整定时扫描的时间间隔和每次扫描的限定耗时，可以在不同情况下使得CPU和内存资源达到最优的平衡效果。
- Redis中同时使用了惰性过期和定期过期两种过期策略。

### Redis key的过期时间和永久有效分别怎么设置？

- EXPIRE和PERSIST命令。

### 我们知道通过expire来设置key 的过期时间，那么对过期的数据怎么处理呢?

- 定时去清理过期的缓存；
- 当有用户请求过来时，再判断这个请求所用到的缓存是否过期，过期的话就去底层系统得到新数据并更新缓存。
- 两者各有优劣，第一种的缺点是维护大量缓存的key是比较麻烦的，第二种的缺点就是每次用户请求过来都要判断缓存失效，逻辑相对比较复杂！具体用哪种方案，大家可以根据自己的应用场景来权衡。

## Redis---Redis事务实现和乐观锁

###  事务的概念和原理

- Redis中的事务（transaction）是一组命令的集合。事务同命令一样都是Redis中的最小执行单位，一个事务中的命令要么都执行，要么都不执行。
- 事务的原理是先将属于一个事务的命令发送给Redis，然后在让Redis一次执行这些命令。

### Redis事务（transaction）提供了以下五个命令，用于用户操作事务功能

- MULTI 标记一个事务块的开始
- DISCARD 放弃执行事务
- EXEC 执行事务中的所有命令
- WATCH 监视一个或多个key，如果至少有一个key在EXEC之前被修改，则放弃执行事务
- UNWATCH 取消WATCH命令对所有键的监视
- 在关系数据库事务提供回滚（rollback）功能，但是redis不支持，因为redis在事务上保持简洁和快速。单线程，直接不提交就完事了

### Redis保证一个事务中的所有命令要么被都不执行，要么都执行。
如果在发送EXEC命令前客户端断线了，则Redis会清空事务队列，事务中的所有命令都不会执行；
一旦客户端发送了EXEC命令，所有的命令都会被执行，即使伺候客户端断线也没关系，因为Redis会记录所有要执行的命令。

### . 事务的实现

- 1.开始事务

	- 在客户端执行一个MULTI命令，标记一个事务块的开始。该命令会被封装成Redis协议的格式发送给服务器，服务器接收到该命令会调用multiCommand()函数来执行

- 2.命令入队

	- 由于事务的命令是一次性、按顺序的执行，因此，需要将客户端中的所有事务命令事前保存起来。
	- 如果当前客户端处于事务状态，并且当前执行的命令不是EXEC、DISCARD、MULTI和WATCH命令，那么调用queueMultiCommand()函数将当前命令入队。

- 3.执行事务

	- 当事务命令全部入队后，在客户端执行EXEC命令，就可以执行事务。服务器会调用execCommand()函数来执行EXEC命令。

## 流程

