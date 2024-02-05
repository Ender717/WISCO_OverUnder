#ifndef WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP
#define WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP

#include "IAutonomous.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for autonomous routines
 * @author Nathan Sandvig
 * 
 */
namespace autons
{
class BlueSkillsAuton : public IAutonomous
{
private:
    /**
     * @brief The name of the autonomous
     * 
     */
    static constexpr char AUTONOMOUS_NAME[]{"B_SKILLS"};

public:
    /**
	 * @brief Get the name of the autonomous
	 *
	 * @return std::string The name of the autonomous
	 */
	std::string getName() override;

	/**
	 * @brief Initialize the autonomous
	 *
	 */
	void initialize(std::shared_ptr<robot::Robot> robot) override;

	/**
	 * @brief Run the autonomous
	 *
	 */
	void run(std::shared_ptr<robot::Robot> robot) override;
};
}
}

#endif