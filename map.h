// 头文件
#ifndef MAP_H
#define MAP_H
#define MAX_ROWS 25 // 地图最大行数
#define MAX_COLS 40 // 地图最大列数

// 定义地图元素
#define QIANG '#'         // 墙
#define DOUZI '.'         // 豆子
#define NENGLIANG_DOU 'O' // 能量豆
#define KONGBAI ' '       // 空地
#define PACMAN_QISHI 'P'  // 玩家起始位置
#define YOULING_QISHI 'G' // 幽灵起始位置
#define SHUIGUO 'F'       // 水果奖励

// 地图难度分级
typedef enum
{
    JIANDAN = 1, // 简单地图
    GAOJI = 2    // 高级地图
} DituNandu;

// 地图信息
typedef struct
{
    char ditu[MAX_ROWS][MAX_COLS]; // 存储地图的二维数组
    int hangshu;                   // 地图实际行数
    int lieshu;                    // 地图实际列数
    int zong_douzishu;             // 总豆子数量
    int shengyu_douzishu;          // 剩余豆子数量
    int nengliangdoushu;           // 能量豆数量
    int you_shuiguo;               // 有无水果
    DituNandu nandu;               // 地图难度
    int pacman_qishi_hang;         // Pac-Man起始行
    int pacman_qishi_lie;          // Pac-Man起始列
    int youling_qishi_hang[4];     // 4个幽灵的起始行
    int youling_qishi_lie[4];      // 4个幽灵的起始列
    int youling_shuliang;          // 幽灵总数量
} Ditu;

// 函数声明
void chushihua_ditu(Ditu *ditu, DituNandu nandu);                                   // 地图初始化
void xianshi_ditu(const Ditu *ditu);                                                // 显示地图
int shi_qiang(const Ditu *ditu, int hang, int lie);                                 // 检查墙体
int shi_suidao(const Ditu *ditu, int hang, int lie);                                // 检查隧道
int chi_douzi(Ditu *ditu, int hang, int lie);                                       // 吃豆得分
void huoqu_pacman_qishi(const Ditu *ditu, int *hang, int *lie);                     // 获取玩家起始位置
void huoqu_youling_qishi(const Ditu *ditu, int youling_index, int *hang, int *lie); // 获取幽灵起始位置
int huoqu_youling_shuliang(const Ditu *ditu);                                       // 获取幽灵数量
int you_nengliangdou(const Ditu *ditu);                                             // 检查有无能量豆
int zhichi_shuiguo(const Ditu *ditu);                                               // 检查是否支持水果
int jihuo_nengliangdou(Ditu *ditu, int hang, int lie);                              // 激活能量豆
void chongzhi_ditu(Ditu *ditu);                                                     // 重启地图

#endif // 结束头文件