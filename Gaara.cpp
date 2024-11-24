#include "Gaara.h"
#include <bits/stdc++.h>
#include "Constants.h"
#include "Platform.h"

Gaara::Gaara() : Character() {
	left = false;
	position = { 100.f, GROUND };
	loadResources("D:\\D1\\code\\bvn\\access\\gaaraS\\gaara", "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\section.txt", "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\origins.txt");
}

Gaara::Gaara(int flag) : Character() {
	left = true;
	position = { 300.f, GROUND };
	loadResources("D:\\D1\\code\\bvn\\access\\gaaraS\\gaara", "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\section.txt", "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\origins.txt");
}

void Gaara::takeDamage(int amount) {

}
