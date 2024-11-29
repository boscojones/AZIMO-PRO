-- Script Lua para NM Lake
local function calculate_holo_effect(input_data)
    -- Simulação de efeito Holo em NM Lake
    local effect = {}
    for i, value in ipairs(input_data) do
        effect[i] = value * math.random() -- Efeito aleatório
    end
    return effect
end

local input_data = {1, 2, 3, 4, 5}
local holo_effect = calculate_holo_effect(input_data)

for i, value in ipairs(holo_effect) do
    print("Holo Effect for", input_data[i], "is", value)
end
