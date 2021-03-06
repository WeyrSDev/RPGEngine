#include "InputManager.h"
#include "..\UI\UIManager.h"

StrongComponentPtr InputManager::CreateInputComponent()
{
	shared_ptr<InputComponent> newComponent(new InputComponent);
	m_inputComponents.push_back(newComponent);
	return newComponent;
}

void InputManager::Update(float dt, sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::I)
			m_inventoryOpen = !m_inventoryOpen;
		else if (event.key.code == sf::Keyboard::E)
			m_equipmentOpen = !m_equipmentOpen;
	}
		
	if (event.type == sf::Event::MouseButtonPressed)
	{

		if (m_inventoryOpen || m_equipmentOpen)
			m_uiManager->HandleInput(event, sf::Mouse::getPosition(window));
	}

	for (vector<shared_ptr<InputComponent>>::iterator it = m_inputComponents.begin(); it != m_inputComponents.end();)
	{
		if (!(*it)->GetInUse())
			it = m_inputComponents.erase(it);
		else
		{
			(*it)->Update(dt, event);
			++it;
		}
	}
}

vector<shared_ptr<InputComponent>> InputManager::m_inputComponents;