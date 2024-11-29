-- Script Lua para Tracing NBH Posh Sea Learning
local function tracing_algorithm(data)
    -- Algoritmo de tracing
    local result = {}
    for i, value in ipairs(data) do
        result[i] = value * 2 -- Exemplo de processamento
    end
    return result
end

local input_data = {10, 20, 30}
local traced_data = tracing_algorithm(input_data)

for i, value in ipairs(traced_data) do
    print("Traced Value:", value)
end
