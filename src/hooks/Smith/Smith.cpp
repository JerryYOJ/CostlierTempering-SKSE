#include "Smith.h"
#include "../../configmanager.h"

#include <MinHook.h>

static std::map<RE::FormID, std::vector<int32_t>> OriginalStored;

void Smith::Install() {
	
	REL::Relocation<std::uintptr_t> addr{ RELOCATION_ID(51460, 51460) };
	MH_CreateHook((void*)addr.address(), UpdateItemCard, (void**)&func_UpdateItemCard);

	ConfigManager::getInstance().HasKey("Multiplier", "1.0");
}

void Smith::UpdateItemCard(RE::CraftingSubMenus::SmithingMenu* menu){
	if (menu->unk160) return func_UpdateItemCard(menu);

	auto cur = menu->unk150; //Current Index
	if(cur >= menu->unk100.size()) return func_UpdateItemCard(menu);

	auto&& constructible = menu->unk100[cur].constructibleObject;
	auto&& items = constructible->requiredItems;

	if (!OriginalStored.contains(constructible->formID)) {
		for (int idx = 0; idx < items.numContainerObjects; idx++) {
			OriginalStored[constructible->formID].push_back(items.containerObjects[idx]->count);
		}
	}

	for (int idx = 0; idx < items.numContainerObjects; idx++) {
		auto orig = OriginalStored[constructible->formID].at(idx);
		auto baseitemRate = menu->unk100[cur].unk18;
		auto finalitemRate = menu->unk100[cur].unk1C;
		float multiplier = std::stof(ConfigManager::getInstance().GetKey("Multiplier"));

		items.containerObjects[idx]->count = std::ceil(std::pow((1.0 + 5.8 * (finalitemRate - baseitemRate)), 2.1) * multiplier);
	}

	return func_UpdateItemCard(menu);
}
