#include <stdio.h>
#include "map.h"  // 包含地图头文件

// 测试地图功能
void ceshi_ditu_gongneng() {
    Ditu ditu1, ditu2;
    
    printf("=== 简单地图测试 ===\n");
    chushihua_ditu(&ditu1, JIANDAN);
    xianshi_ditu(&ditu1);
    
    int pacman_hang, pacman_lie;
    huoqu_pacman_qishi(&ditu1, &pacman_hang, &pacman_lie);
    printf("Pac-Man 起始位置: (%d, %d)\n", pacman_hang, pacman_lie);
    printf("幽灵数量: %d\n", huoqu_youling_shuliang(&ditu1));
    printf("总豆子数: %d\n", ditu1.zong_douzishu);
    printf("有能量豆: %s\n", you_nengliangdou(&ditu1) ? "是" : "否");
    
    printf("\n=== 高级地图测试 ===\n");
    chushihua_ditu(&ditu2, GAOJI);
    xianshi_ditu(&ditu2);
    
    huoqu_pacman_qishi(&ditu2, &pacman_hang, &pacman_lie);
    printf("Pac-Man 起始位置: (%d, %d)\n", pacman_hang, pacman_lie);
    printf("幽灵数量: %d\n", huoqu_youling_shuliang(&ditu2));
    printf("总豆子数: %d\n", ditu2.zong_douzishu);
    printf("能量豆数量: %d\n", ditu2.nengliangdoushu);
    printf("支持水果奖励: %s\n", zhichi_shuiguo(&ditu2) ? "是" : "否");
    
    printf("\n测试吃豆子功能:\n");
    int defen = chi_douzi(&ditu2, 1, 1);
    printf("吃豆子得分: %d, 剩余豆子: %d\n", defen, ditu2.shengyu_douzishu);
}

// 主函数
int main() {
    ceshi_ditu_gongneng();
    return 0;
}