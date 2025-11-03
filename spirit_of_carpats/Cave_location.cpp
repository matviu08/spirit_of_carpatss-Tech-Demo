#include "Cave_location.h"
#include "location.h" // <- ensure generate_Cave_map declaration is visible

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;
const float WORLD_WIDTH_METERS = 77.0f / 2.0f;
const float WORLD_HEIGHT_METERS = 20.0f;
const float wallHalfWidth = 0.5f;
const float WINDOW_SCALE = 384.0f;
extern bool levelStarted;


//enum AnimationState {
//	IDLE,
//	WALKING_LEFT,
//	WALKING_RIGHT
//};


void Cave_location(RenderWindow& window, Sprite& background, Text& backButtonSettings,
	Player& pl, Font& font, const optional<Event>& event, Menu& menu)
{
	Vector2u windowSize = window.getSize();
	/*AnimationState currentAnimation = IDLE;
	AnimationState lastAnimation;*/

	const float REFERENCE_WIDTH = 1920.0f;
	const float REFERENCE_HEIGHT = 1080.0f;
	float scaleFactorX = (float)windowSize.x / REFERENCE_HEIGHT;
	float scaleFactorY = (float)windowSize.y / REFERENCE_WIDTH;
	float uniformScale = min(scaleFactorX, scaleFactorY);

	float screenGroundY = -((float)windowSize.y * 0.42f) / SCALE;
	float screenCenterY = 0.0f;
	float wallHalfHeight = ((float)windowSize.y * 0.5f) / SCALE;

	b2WorldDef worldDef = b2DefaultWorldDef();

	//....

	
	

	
	Texture caveBackgroundTexture;
	Texture caveFloorTexture;
	Texture spiritTexture;
	Texture chestTexture;
	Texture rock; 


	caveBackgroundTexture.loadFromFile("assets/img/caves_bg.png");
	caveFloorTexture.loadFromFile("assets/img/ground_to_cave.jpg");

	vector<Sprite> caveBackground;
	vector<Sprite> caveFloor;
	vector<Sprite> caveSpirit;
	vector<Sprite> caveChest;
	vector<Sprite> caveRock;

	generate_Cave_map(
		window,
		chestTexture,           
		spiritTexture,         
		rock,                   
		caveBackgroundTexture,  
		background,            
		caveSpirit,             
		caveChest,              
		caveRock                
	);


}