#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Map.h"
#include "Bullet.h"


const int PLAYER_SPEED = 5; // T?c ?? di chuy?n c?a nh�n v?t
const float GRAVITY = 0.5f; // Tr?ng l?c
const float JUMP_FORCE = 15.0f; // L?c nh?y
const float MAX_FALL_SPEED = 10.0f; // T?c ?? r?i t?i ?a c?a nh�n v?t
const Uint32 ATTACK_COOLDOWN = 500; // Th?i gian h?i chi�u tr�nh spam 


// Tr?ng th�i nh�n v?t
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
	static Mix_Chunk* swordSound; // �m thanh ch�m
	static Mix_Chunk* gunSound; // �m thanh b?n

	SDL_Rect srcRect, destRect;	// Khung ?nh g?c v� v? tr� v? nh�n v?t
	float dx, dy; // V?n t?c theo tr?c x v� y
	std::vector<SDL_Texture*> textures; // Texture c?a nh�n v?t
	int health; // M�u
	bool isJumping; // Check xem nh�n v?t c� ?ang nh?y kh�ng
	Uint32 lastAttackTime = 0; // Th?i gian l?n ?�nh cu?i c�ng
	PlayerState state = IDLERIGHT; // Tr?ng th�i hi?n t?i
	int startX, startY; // V? tr� ban ??u
	std::vector<Bullet> bullets; // Danh s�ch ??n c?a nh�n v?t
	std::vector<SDL_Texture*> bulletTexture; // Danh s�ch ?nh ??n
	bool facingRight = true; // H??ng quay c?a nh�n v?t
	bool isSwordAttacking; // Check nh�n v?t c� ?ang ch�m kh�ng
	bool isShooting; // Check xem nh�n v?t c� ?ang b?n kh�ng
	bool hasDealtSwordDamage; // Check xem nh�n v?t ?� g�y s�t th??ng b?ng ki?m trong l?n ch�m n�y ch?a
	Uint32 lastFrameTime = 0; // Frame cu?i 
	SDL_Rect swordRect; // K�ch th??c ki?m

	int shootAnimFrame = 0; // Khung hi?n t?i c?a animation b?n
	Uint32 shootAnimStartTime = 0; // Th?i gian b?t ??u animation b?n

	int swordAnimFrame = 0; // Khung hi?n t?i c?a animation ch�m
	Uint32 swordAnimStartTime = 0; // Th?i gian b?t ??u animation ch�m

	bool isDead; // Ki?m tra xem nh�n v?t ?� ch?t ch?a             
	Uint32 deathTime = 0; // Th?i ?i?m ch?t 

	int currentFrame; // Khung h�nh hi?n t?i d�ng ?? v?
	bool isHurting = false; // Check xem nh�n v?t c� b? th??ng kh�ng
	int hurtFrame = 0; // Khung h�nh b? th??ng
	Uint32 hurtStartTime = 0; // th?i ?i?m b?t ??u b? th??ng
	const int hurtDuration = 300; // th?i gian hi?u ?ng b? th??ng 



	// Kh?i t?o
	Player(int x, int y);
	// Ki?m tra c� th? t?n c�ng kh�ng
	bool canAttack();
	// Tr?ng l?c
	void applyGravity();
	// Nh?n s�t th??ng
	void TakeDamage(int dmg);
	// V? ??n
	void RenderBullets(SDL_Renderer* renderer);
	// B?n s�ng
	void Shoot();
	// C?p nh?t ??n
	void UpdateBullets(Player& target, Map& gameMap);
	// Ch�m ki?m
	void SwordAttack();
	// C?p nh?t ki?m
	void UpdateSword(Player& target);
	// C?p nh?t tr?ng th�i ng??i ch?i
	void Update();
	// Render nh�n v?t
	void Render(SDL_Renderer* renderer);
	// Reset l?i nh�n v?t(d�ng khi restart game)
	void reset();
};
