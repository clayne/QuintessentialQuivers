#include "equipmentAdjuster.h"

namespace Adjuster {

	bool AdjustArrows() {

		SKSE::log::info("=============================================================");
		SKSE::log::info("=================Beginning Arrow Adjustment==================");
		SKSE::log::info("=============================================================");
		int totalArrows = 0;

		if (const auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {

			for (const auto& foundArrow : dataHandler->GetFormArray<RE::TESAmmo>()) {

				if ((foundArrow->GetRuntimeData().data.flags & RE::AMMO_DATA::Flag::kNonBolt) && !(foundArrow->GetRuntimeData().data.flags & RE::AMMO_DATA::Flag::kNonPlayable)) {

					if (!(foundArrow->GetRuntimeData().data.damage <= 0)) {

						//Formula Here.
						float originalDamage = foundArrow->GetRuntimeData().data.damage;
						foundArrow->GetRuntimeData().data.damage = floor(std::pow(originalDamage, 2.3) * 0.01 + std::pow(originalDamage, 1.3) * 0.1 + 5.3);
						SKSE::log::info("{} Damage {} -> {}", foundArrow->GetName(), originalDamage, foundArrow->GetRuntimeData().data.damage);
						totalArrows++;
					}
				}
			}
		} 
		else {

			return false;
		}

		SKSE::log::info(" ");
		SKSE::log::info("Number of arrows adjusted: {}", totalArrows);
		SKSE::log::info(" ");
		return true;
	}

	bool AdjustBolts() {

		SKSE::log::info("=============================================================");
		SKSE::log::info("==================Beginning Bolt Adjustment==================");
		SKSE::log::info("=============================================================");
		int totalBolts = 0;

		if (const auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {

			for (const auto& foundBolt : dataHandler->GetFormArray<RE::TESAmmo>()) {

				if (!(foundBolt->GetRuntimeData().data.flags & RE::AMMO_DATA::Flag::kNonBolt) && !(foundBolt->GetRuntimeData().data.flags & RE::AMMO_DATA::Flag::kNonPlayable)) {

					if (!(foundBolt->GetRuntimeData().data.flags == RE::AMMO_DATA::Flag::kNonPlayable)) {

						if (!(foundBolt->GetRuntimeData().data.damage <= 0)) {
							
							float originalDamage = foundBolt->GetRuntimeData().data.damage;
							foundBolt->GetRuntimeData().data.flags.set(RE::AMMO_DATA::Flag::kIgnoresNormalWeaponResistance);
							foundBolt->GetRuntimeData().data.damage = floor(std::pow(originalDamage, 2.3) * 0.01 + std::pow(originalDamage, 1.3) * 0.1 + 5.3);
							SKSE::log::info("{} Damage: {} -> {}, Ignores Armor: {}", foundBolt->GetName(), originalDamage, foundBolt->GetRuntimeData().data.damage, foundBolt->IgnoresNormalWeaponResistance());
							totalBolts++;
						}
					}
				}
			}
		}
		else {

			return false;
		}

		SKSE::log::info(" ");
		SKSE::log::info("Number of bolts adjusted: {}", totalBolts);
		SKSE::log::info(" ");
		return true;
	}

	bool AdjustBows() {

		SKSE::log::info("=============================================================");
		SKSE::log::info("==================Beginning Bow Adjustment===================");
		SKSE::log::info("=============================================================");
		int totalBows = 0;

		if (const auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {

			for (const auto& foundBow : dataHandler->GetFormArray<RE::TESObjectWEAP>()) {

				if (foundBow->IsBow()) {

					if (foundBow->GetPlayable()) {

						if (!(foundBow->GetAttackDamage() <= 0)) {

							foundBow->attackDamage = foundBow->attackDamage - 3;
							SKSE::log::info("{} Damage: {}", foundBow->GetName(), foundBow->GetAttackDamage());
							totalBows++;
						}
					}
				}
			}
		}
		else {

			return false;
		}

		SKSE::log::info(" ");
		SKSE::log::info("Number of bows adjusted: {}", totalBows);
		SKSE::log::info(" ");
		return true;
	}

	bool AdjustCrossbows() {

		SKSE::log::info("=============================================================");
		SKSE::log::info("================Beginning Crossbow Adjustment================");
		SKSE::log::info("=============================================================");
		int totalCrossbows = 0;

		if (const auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {

			for (const auto& foundCrossbow : dataHandler->GetFormArray<RE::TESObjectWEAP>()) {

				if (foundCrossbow->IsCrossbow()) {

					if (foundCrossbow->GetPlayable()) {

						if (!(foundCrossbow->GetAttackDamage() <= 0)) {

							foundCrossbow->attackDamage = foundCrossbow->attackDamage - 1;
							SKSE::log::info("{} Damage: {}.", foundCrossbow->GetName(), foundCrossbow->GetAttackDamage());
							totalCrossbows++;
						}
					}
				}
			}
		}
		else {

			return false;
		}

		SKSE::log::info(" ");
		SKSE::log::info("Number of crossbows adjusted: {}", totalCrossbows);
		SKSE::log::info(" ");
		return true;
	}
}