#include "Game.h" // ���� Game ���ͷ�ļ�
#include <bits/stdc++.h>

//extern "C" {
//    // ���ö���
//    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}


int main() {
    try {
        // ���� Game ʵ�������봰�ڵĿ�ȡ��߶Ⱥͱ���
        Game game(1600, 1200, "My Fighting Game");
        //game.window.setFramerateLimit(70);// ����֡��
        // ������Ϸ��ѭ��
        game.run();
    }
    catch (const std::exception& e) {
        // ��������쳣�����������Ϣ
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
