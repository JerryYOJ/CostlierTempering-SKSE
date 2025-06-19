class Smith {

public:
    static void Install();

protected:
    static void UpdateItemCard(RE::CraftingSubMenus::SmithingMenu* menu);

private:
    Smith() = delete;
    Smith(const Smith&) = delete;
    Smith(Smith&&) = delete;
    ~Smith() = delete;

    Smith& operator=(const Smith&) = delete;
    Smith& operator=(Smith&&) = delete;

    inline static REL::Relocation<decltype(UpdateItemCard)> func_UpdateItemCard;
};