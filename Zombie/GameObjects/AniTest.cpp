#include "pch.h"
#include "AniTest.h"

AniTest::AniTest(const std::string& name) : SpriteGo(name)
{
}

void AniTest::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void AniTest::Reset()
{
	animator.Play("animations/Idle.csv");
	SetOrigin(Origins::BC);
	isGrounded = true;
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	// 좌우 이동
	float h = InputMgr::GetAxisRaw(Axis::Horizontal);
	velocity.x = h * speed * dt;

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}

	if (animator.GetCurrentClipId() == "animations/Idle.csv")
	{
		if (h != 0.f)
		{
			animator.Play("animations/Run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "animations/Run.csv")
	{
		if (h == 0.f)
		{
			animator.Play("animations/Idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "animations/Jump.csv" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/Idle.csv");
		}
		else
		{
			animator.Play("animations/Run.csv");
		}
	}

	// 점프
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		animator.Play("animations/Jump.csv");
		velocity.y = -500.f;
	}

	velocity.y += gravity * dt;

	position += sf::Vector2f(velocity.x, velocity.y * dt);
	SetPosition(position);

	if (position.y > 0.f)
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	/*sf::Vector2f pos;
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		SetScale(sf::Vector2f(1.f, 1.f));
		animator.Play("Run");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		SetScale(sf::Vector2f(-1.f, 1.f));
		animator.Play("Run");
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::D)
		|| InputMgr::GetKeyUp(sf::Keyboard::A))
	{
		animator.Play("Idle");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isJumping = true;
		animator.Play("Jump");
	}

	if (isJumping)
	{
		velocity += acceleration * dt;
		pos.y = position.y + velocity * dt;

		if (pos.y > 0)
		{
			isJumping = false;
			velocity = -500.f;
			pos.y = 0.f;
			animator.Play("Idle");
		}
	}
	pos.x = position.x + direction.x * speed * dt;
	SetPosition(pos);*/
}
