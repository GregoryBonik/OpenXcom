/*
 * Copyright 2010 Daniel Albano
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "PurchaseState.h"
#include <string>
#include "../Engine/Game.h"
#include "../Resource/ResourcePack.h"
#include "../Engine/Language.h"
#include "../Resource/LangString.h"
#include "../Engine/Font.h"
#include "../Engine/Palette.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextList.h"
#include "../Savegame/SavedGame.h"

/**
 * Initializes all the elements in the Purchase/Hire screen.
 * @param game Pointer to the core game.
 */
PurchaseState::PurchaseState(Game *game) : State(game)
{
	// Create objects
	_window = new Window(this, 320, 200, 0, 0);
	_btnOk = new TextButton(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 148, 16, 8, 176);
	_btnCancel = new TextButton(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 148, 16, 164, 176);
	_txtTitle = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 310, 16, 5, 8);
	_txtFunds = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 150, 9, 10, 24);
	_txtPurchases = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 150, 9, 160, 24);
	_txtItem = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 140, 9, 10, 32);
	_txtCost = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 102, 9, 152, 32);
	_txtQuantity = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 60, 9, 256, 32);
	_lstItems = new TextList(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 286, 128, 10, 40);
	
	// Set palette
	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(0)), Palette::backPos, 16);

	add(_window);
	add(_btnOk);
	add(_btnCancel);
	add(_txtTitle);
	add(_txtFunds);
	add(_txtPurchases);
	add(_txtItem);
	add(_txtCost);
	add(_txtQuantity);
	add(_lstItems);

	// Set up objects
	_window->setColor(Palette::blockOffset(13)+13);
	_window->setBackground(game->getResourcePack()->getSurface("BACK13.SCR"));

	_btnOk->setColor(Palette::blockOffset(13)+13);
	_btnOk->setText(_game->getResourcePack()->getLanguage()->getString(STR_OK));
	_btnOk->onMouseClick((EventHandler)&PurchaseState::btnOkClick);

	_btnCancel->setColor(Palette::blockOffset(13)+13);
	_btnCancel->setText(_game->getResourcePack()->getLanguage()->getString(STR_CANCEL));
	_btnCancel->onMouseClick((EventHandler)&PurchaseState::btnCancelClick);

	_txtTitle->setColor(Palette::blockOffset(13)+10);
	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(_game->getResourcePack()->getLanguage()->getString(STR_PURCHASE_HIRE_PERSONNEL));

	std::string s = _game->getResourcePack()->getLanguage()->getString(STR_CURRENT_FUNDS);
	s += Text::formatFunding(_game->getSavedGame()->getFunds());
	_txtFunds->setColor(Palette::blockOffset(13)+10);
	_txtFunds->setText(s);

	_txtPurchases->setColor(Palette::blockOffset(13)+10);
	_txtPurchases->setText(_game->getResourcePack()->getLanguage()->getString(STR_COST_OF_PURCHASES));

	_txtItem->setColor(Palette::blockOffset(13)+10);
	_txtItem->setText(_game->getResourcePack()->getLanguage()->getString(STR_ITEM));

	_txtCost->setColor(Palette::blockOffset(13)+10);
	_txtCost->setText(_game->getResourcePack()->getLanguage()->getString(STR_COST_PER_UNIT_UC));

	_txtQuantity->setColor(Palette::blockOffset(13)+10);
	_txtQuantity->setText(_game->getResourcePack()->getLanguage()->getString(STR_QUANTITY_UC));

	_lstItems->setColor(Palette::blockOffset(13)+10);
	_lstItems->setColumns(3, 162, 92, 32);
	_lstItems->setSelectable(true);
	_lstItems->setBackground(_window);
	_lstItems->addRow(0, 3, "Soldier", "40 000", "0");
}

/**
 *
 */
PurchaseState::~PurchaseState()
{
	
}

void PurchaseState::btnOkClick(SDL_Event *ev, int scale)
{
	
}

/**
 * Returns to the previous screen.
 * @param ev Pointer to the SDL_Event.
 * @param scale Scale of the screen.
 */
void PurchaseState::btnCancelClick(SDL_Event *ev, int scale)
{
	_game->popState();
}