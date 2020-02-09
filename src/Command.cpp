#include <c-assignment/Command.hpp>
#include <c-assignment/CommandResources.hpp>

namespace cassign
{
	Command::Command(const std::string name, CommandResources* commandResources)
		: m_name(name)
		, m_commandResources(commandResources)
	{}

	void Command::initialize()
	{
		m_commandResources->addAllowedCommand(this);
	}

	const std::string Command::getName() const
	{
		return m_name;
	}
}