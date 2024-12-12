#include "Game.h" // 包含 Game 类的头文件
#include <bits/stdc++.h>


//extern "C" {
//    // 换用独显
//    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}

int main() {
    try {
        // 创建 Game 实例，传入窗口的宽度、高度和标题
        Game game(1600, 1200, "My Fighting Game");
        game.window.setFramerateLimit(70);// 限制帧率
        // 启动游戏主循环
        game.run();
    }
    catch (const std::exception& e) {
        // 如果发生异常，输出错误信息
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}