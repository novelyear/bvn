#include "Game.h" // ���� Game ���ͷ�ļ�
#include <bits/stdc++.h>


int main() {
    try {
        // ���� Game ʵ�������봰�ڵĿ�ȡ��߶Ⱥͱ���
        Game game(1600, 1200, "My Fighting Game");

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
