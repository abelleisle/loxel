Stock = {name = "",
		 price = 0}

function Stock:new(o, name, price)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	self.name = name or ""
	self.price = price or 0
	return o
end

Bitcoin = Stock:new(nil, "Bitcoin", 19000)
