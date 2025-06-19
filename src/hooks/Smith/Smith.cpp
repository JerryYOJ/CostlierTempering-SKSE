#include "Smith.h"
#include "../../configmanager.h"

#include <MinHook.h>

static std::map<RE::FormID, std::vector<int32_t>> OriginalStored;

void Smith::Install() {
	
	REL::Relocation<std::uintptr_t> addr{ RELOCATION_ID(51448, 51448) };
	MH_CreateHook((void*)addr.address(), DetermineCanCraftSmithingRecipe, (void**)&func_DetermineCanCraftSmithingRecipe);

	ConfigManager::getInstance().HasKey("Multiplier", "1.0");
}

void Smith::DetermineCanCraftSmithingRecipe(RE::GFxValue* element, RE::CraftingSubMenus::SmithingMenu::SmithingItemEntry* entry, RE::CraftingSubMenus::SmithingMenu* menu){
	auto&& constructible = entry->constructibleObject;
	auto&& items = constructible->requiredItems;

	if (!OriginalStored.contains(constructible->formID)) {
		for (int idx = 0; idx < items.numContainerObjects; idx++) {
			OriginalStored[constructible->formID].push_back(items.containerObjects[idx]->count);
		}
	}

	for (int idx = 0; idx < items.numContainerObjects; idx++) {
		auto orig = OriginalStored[constructible->formID].at(idx);
		auto baseitemRate = entry->unk18;
		auto finalitemRate = entry->unk1C;
		float multiplier = std::stof(ConfigManager::getInstance().GetKey("Multiplier"));

		items.containerObjects[idx]->count = std::ceil(std::pow((1.0 + 5.8 * (finalitemRate - baseitemRate)), 2.1) * multiplier);
	}

	static REL::Relocation<std::byte(RE::BGSConstructibleObject*)> HasRequiredItems{ RELOCATION_ID(16916, 16916) };
	entry->unk28 = HasRequiredItems(constructible);

	return func_DetermineCanCraftSmithingRecipe(element, entry, menu);
}
