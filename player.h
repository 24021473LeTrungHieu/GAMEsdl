#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Map.h"
#include "Bullet.h"


const int PLAYER_SPEED = 5; // T?c ?? di chuy?n c?a nhân v?t
const float GRAVITY = 0.5f; // Tr?ng l?c
const float JUMP_FORCE = 15.0f; // L?c nh?y
const float MAX_FALL_SPEED = 10.0f; // T?c ?? r?i t?i ?a c?a nhân v?t
const Uint32 ATTACK_COOLDOWN = 500; // Th?i gian h?i chiêu tránh spam 


// Tr?ng thái nhân v?t
enum PlayerState {
	IDLERIGHT,
	IDLELEFT,
	RUNRIGHT,
	RUNLEFT,
	JUMPRIGHT,
	JUMPLEFT,
	SWORDATTACKRIGHT,
	SWORDATTACKLEFT,
	SHOTRIGHT,
	SHOTLEFT,
	DEADRIGHT,
	DEADLEFT,
	HURTRIGHT,
	HURTLEFT
};


struct Player
{
	static Mix_Chunk* swordSound; // Âm thanh chém
	static Mix_Chunk* gunSound; // Âm thanh b?n

	SDL_Rect srcRect, destRect;	// Khung ?nh g?c và v? trí v? nhân v?t
	float dx, dy; // V?n t?c theo tr?c x và y
	std::vector<SDL_Texture*> textures; // Texture c?a nhân v?t
	int health; // Máu
	bool isJumping; // Check xem nhân v?t có ?ang nh?y không
	Uint32 lastAttackTime = 0; // Th?i gian l?n ?ánh cu?i cùng
	PlayerState state = IDLERIGHT; // Tr?ng thái hi?n t?i
	int startX, startY; // V? trí ban ??u
	std::vector<Bullet> bullets; // Danh sách ??n c?a nhân v?t
	std::vector<SDL_Texture*> bulletTexture; // Danh sách ?nh ??n
	bool facingRight = true; // H??ng quay c?a nhân v?t
	bool isSwordAttacking; // Check nhân v?t có ?ang chém không
	bool isShooting; // Check xem nhân v?t có ?ang b?n không
	bool hasDealtSwordDamage; // Check xem nhân v?t ?ã gây sát th??ng b?ng ki?m trong l?n chém này ch?a
	Uint32 lastFrameTime = 0; // Frame cu?i 
	SDL_Rect swordRect; // Kích th??c ki?m

	int shootAnimFrame = 0; // Khung hi?n t?i c?a animation b?n
	Uint32 shootAnimStartTime = 0; // Th?i gian b?t ??u animation b?n

	int swordAnimFrame = 0; // Khung hi?n t?i c?a animation chém
	Uint32 swordAnimStartTime = 0; // Th?i gian b?t ??u animation chém

	bool isDead; // Ki?m tra xem nhân v?t ?ã ch?t ch?a             
	Uint32 deathTime = 0; // Th?i ?i?m ch?t 

	int currentFrame; // Khung hình hi?n t?i dùng ?? v?
	bool isHurting = false; // Check xem nhân v?t có b? th??ng không
	int hurtFrame = 0; // Khung hình b? th??ng
	Uint32 hurtStartTime = 0; // th?i ?i?m b?t ??u b? th??ng
	const int hurtDuration = 300; // th?i gian hi?u ?ng b? th??ng 



	// Kh?i t?o
	Player(int x, int y);
	// Ki?m tra có th? t?n công không
	bool canAttack();
	// Tr?ng l?c
	void applyGravity();
	// Nh?n sát th??ng
	void TakeDamage(int dmg);
	// V? ??n
	void RenderBullets(SDL_Renderer* renderer);
	// B?n súng
	void Shoot();
	// C?p nh?t ??n
	void UpdateBullets(Player& target, Map& gameMap);
	// Chém ki?m
	void SwordAttack();
	// C?p nh?t ki?m
	void UpdateSword(Player& target);
	// C?p nh?t tr?ng thái ng??i ch?i
	void Update();
	// Render nhân v?t
	void Render(SDL_Renderer* renderer);
	// Reset l?i nhân v?t(dùng khi restart game)
	void reset();
};
