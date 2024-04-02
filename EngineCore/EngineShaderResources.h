#pragma once

// Ό³Έν :
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;

public:

protected:

private:
	void ShaderResourcesCheck(std::string_view _EntryName, ID3DBlob* _ShaderCode);

};

