class Smith {

public:
    static void Install();

protected:
    static void DetermineCanCraftSmithingRecipe(RE::GFxValue* element,RE::CraftingSubMenus::SmithingMenu::SmithingItemEntry* entry,RE::CraftingSubMenus::SmithingMenu* menu);

private:
    Smith() = delete;
    Smith(const Smith&) = delete;
    Smith(Smith&&) = delete;
    ~Smith() = delete;

    Smith& operator=(const Smith&) = delete;
    Smith& operator=(Smith&&) = delete;

    inline static REL::Relocation<decltype(DetermineCanCraftSmithingRecipe)> func_DetermineCanCraftSmithingRecipe;
};