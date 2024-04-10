#pragma once

class ABossFarmMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ABossFarmMap();
	~ABossFarmMap();

	// delete Function
	ABossFarmMap(const ABossFarmMap& _Other) = delete;
	ABossFarmMap(ABossFarmMap&& _Other) noexcept = delete;
	ABossFarmMap& operator=(const ABossFarmMap& _Other) = delete;
	ABossFarmMap& operator=(ABossFarmMap&& _Other) noexcept = delete;

protected:

private:

};

