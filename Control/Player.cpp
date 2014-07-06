//
//  Player.cpp
//  World
//
//  Created by Adam James Leuer on 5/31/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Player.h"

using namespace std ;

unsigned Player::IDs = 0 ;
Pos2<float> Player::defaultStartingPosition = Pos2<float>((globalMaxX() / 2) + FastRand<int>::defaultRandom(-20, 20), (globalMaxY() - (globalMaxY() * 0.25)), 0) ;
AssetType Player::defaultPCAssetType = AssetType::playerShip ; /* change if needed */
float Player::defaultSize = 1.00 ;

Player * Player::defaultPlayer0 = nullptr ;
Player * Player::defaultPlayer1 = nullptr ;

void Player::initDefaultPlayers() {
	defaultPlayer0 = new Player("Player 0", "Ship1_Green.png", Colors::green, defaultSize, defaultStartingPosition, "Green",
									Reaction::friendly, DoA::nodoa, CharacterState::idle, 500, 100) ;
	
	defaultPlayer1 = new Player("Player 1", "Ship2_Blue.png", Colors::blue, defaultSize, defaultStartingPosition, "Blue",
									Reaction::friendly, DoA::nodoa, CharacterState::idle, 500, 100) ;
}

Player::Player() :
	ID(IDs),
	name(""),
	playerCharacter(Colors::blue, defaultPCAssetType, AssetFileIO::getRandomImageFile(defaultPCAssetType).fileName, defaultSize,
					defaultStartingPosition,"", Reaction::friendly, DoA::nodoa, CharacterState::idle, 500, 100)
{
	IDs++ ;
	setNames() ;
	setText() ;
	registerForCallbacks() ;
}

Player::Player(const string & name, const string & playerCharacter_imageFilename,
	Colors playerCharacter_color, float playerCharacter_size, const Pos2<float> & playerCharacter_loc, const string & playerCharacter_name,
	Reaction playerCharacter_reaction, DoA playerCharacter_alive, CharacterState playerCharacter_state,
	unsigned playerCharacter_health, unsigned playerCharacter_damage) :

	ID(IDs),
	name(name),
	playerCharacter(playerCharacter_color, defaultPCAssetType, playerCharacter_imageFilename, playerCharacter_size,
		playerCharacter_loc, playerCharacter_name, playerCharacter_reaction, playerCharacter_alive, playerCharacter_state,
		playerCharacter_health, playerCharacter_damage)
{
	IDs++ ;
	setNames() ;
	setText() ;
	registerForCallbacks() ;
}

void Player::update() {
	//todo
}

void Player::setNames() {
	if (name == "") {
		name = "Player " + to_string(ID) ;
	}
	if (playerCharacter.getName() == "") {
		playerCharacter.setName(name + "'s Character") ;
	}
}

void Player::registerForCallbacks() {
	
	//todo make more generic
	if (playerCharacter.getColor() != Colors::green) {
		KeyInputRegister * onMoveUpKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveUp),
															{MOVE_UP}, {SDLK_UP}, KeypressEvaluationMethod::any) ;
		KeyInputRegister * onMoveDownKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveDown),
															{MOVE_DOWN}, {SDLK_DOWN}, KeypressEvaluationMethod::any) ;
		KeyInputRegister * onMoveLeftKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveLeft),
															  {MOVE_LEFT}, {SDLK_LEFT}, KeypressEvaluationMethod::any) ;
		KeyInputRegister * onMoveRightKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveRight),
															   {MOVE_RIGHT}, {SDLK_RIGHT}, KeypressEvaluationMethod::any) ;
		InputController::registerForKeypress(onMoveUpKey) ;
		InputController::registerForKeypress(onMoveDownKey) ;
		InputController::registerForKeypress(onMoveLeftKey) ;
		InputController::registerForKeypress(onMoveRightKey) ;
	}
	else if (playerCharacter.getColor() != Colors::blue) {
		
		KeyInputRegister * onMoveUpKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveUp),
															{SDLK_KP_8}, KeypressEvaluationMethod::exactlyOne) ;
		KeyInputRegister * onMoveDownKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveDown),
															  {SDLK_KP_2}, KeypressEvaluationMethod::exactlyOne) ;
		KeyInputRegister * onMoveLeftKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveLeft),
															  {SDLK_KP_4}, KeypressEvaluationMethod::exactlyOne) ;
		KeyInputRegister * onMoveRightKey = new KeyInputRegister(&playerCharacter, (&GameInterface::moveRight),
															   {SDLK_KP_6}, KeypressEvaluationMethod::exactlyOne) ;
		
		/*
		KeyInputRegister * onMoveUpRightKeys = new KeyInputRegister(&playerCharacter, (&GameInterface::moveUpRight),
															{SDLK_KP_8, SDLK_KP_6}, KeypressEvaluationMethod::all) ;
		KeyInputRegister * onMoveDownRightKeys = new KeyInputRegister(&playerCharacter, (&GameInterface::moveDownRight),
															  {SDLK_KP_2, SDLK_KP_6}, KeypressEvaluationMethod::all) ;
		KeyInputRegister * onMoveUpLeftKeys = new KeyInputRegister(&playerCharacter, (&GameInterface::moveUpLeft),
															  {SDLK_KP_8, SDLK_KP_4}, KeypressEvaluationMethod::all) ;
		KeyInputRegister * onMoveDownLeftKeys = new KeyInputRegister(&playerCharacter, (&GameInterface::moveDownLeft),
															   {SDLK_KP_2, SDLK_KP_4}, KeypressEvaluationMethod::all) ;  */
		InputController::registerForKeypress(onMoveUpKey) ;
		InputController::registerForKeypress(onMoveDownKey) ;
		InputController::registerForKeypress(onMoveLeftKey) ;
		InputController::registerForKeypress(onMoveRightKey) ;
		
		/*
		InputController::registerForKeypress(onMoveUpRightKeys) ;
		InputController::registerForKeypress(onMoveDownRightKeys) ;
		InputController::registerForKeypress(onMoveUpLeftKeys) ;
		InputController::registerForKeypress(onMoveDownLeftKeys) ; */
	}
}

void Player::setText() {
	
	auto textoutp_lambd = [&, this] () -> void {
		
		stringstream stream ;
		stream << "Player " << this->ID << "'s " << playerCharacter.getVector()->getVelocity() ;
		unsigned x = (globalMaxX() / 10) ;
		unsigned y = (globalMaxX() * 0.75) ;
		string str(stream.str()) ;
		
		Position<float> * pos = new Position<float>(x, y, 0) ;
		Size<int> * size = new Size<int>(128, 128) ;
		GameColor color_fg(0x00, 0x00, 0x00, 0x00) ;
		GameColor color_bg(0x00, 0x00, 0x00, 0x00) ;
		
		TextOutput out(&str, pos, size, &color_fg, &color_bg) ;
		
		while (GLOBAL_CONTINUE_SIGNAL) {
			stream << "Player " << this->ID << "'s " << playerCharacter.getVector()->getVelocity() ;
			str = stream.str() ;
			out.update() ;
			this_thread::sleep_for(chrono::milliseconds(32)) ;
		}
		
	} ;
	
	thread thr(textoutp_lambd) ;
	thr.detach() ;
}







