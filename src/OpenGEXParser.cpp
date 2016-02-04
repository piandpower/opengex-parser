#include "OpenGEXPCH.h"
#include "OpenGEXParser.h"
#include "openddlparser/OpenDDLParser.h"

USE_ODDLPARSER_NS

namespace Grammar {
	static const std::string MetricType = "Metric";
	static const std::string Metric_DistanceType = "distance";
	static const std::string Metric_AngleType = "angle";
	static const std::string Metric_TimeType = "time";
	static const std::string Metric_UpType = "up";
	static const std::string NameType = "Name";
	static const std::string ObjectRefType = "ObjectRef";
	static const std::string MaterialRefType = "MaterialRef";
	static const std::string MetricKeyType = "key";
	static const std::string GeometryNodeType = "GeometryNode";
	static const std::string GeometryObjectType = "GeometryObject";
	static const std::string TransformType = "Transform";
	static const std::string MeshType = "Mesh";
	static const std::string VertexArrayType = "VertexArray";
	static const std::string IndexArrayType = "IndexArray";
	static const std::string MaterialType = "Material";
	static const std::string ColorType = "Color";
	static const std::string DiffuseColorToken = "diffuse";
	static const std::string SpecularColorToken = "specular";
	static const std::string EmissionColorToken = "emission";

	static const std::string DiffuseTextureToken = "diffuse";
	static const std::string DiffuseSpecularTextureToken = "specular";
	static const std::string SpecularPowerTextureToken = "specular_power";
	static const std::string EmissionTextureToken = "emission";
	static const std::string OpacyTextureToken = "opacity";
	static const std::string TransparencyTextureToken = "transparency";
	static const std::string NormalTextureToken = "normal";

	static const char *TextureType = "Texture";

	enum TokenType {
		NoneType = -1,
		MetricToken,
		NameToken,
		ObjectRefToken,
		MaterialRefToken,
		MetricKeyToken,
		GeometryNodeToken,
		GeometryObjectToken,
		TransformToken,
		MeshToken,
		VertexArrayToken,
		IndexArrayToken,
		MaterialToken,
		ColorToken,
		TextureToken
	};

	static TokenType matchTokenType(const char *tokenType) {
		if (MetricType == tokenType) {
			return MetricToken;
		}
		else if (NameType == tokenType) {
			return NameToken;
		}
		else if (ObjectRefType == tokenType) {
			return ObjectRefToken;
		}
		else if (MaterialRefType == tokenType) {
			return MaterialRefToken;
		}
		else if (MetricKeyType == tokenType) {
			return MetricKeyToken;
		}
		else if (GeometryNodeType == tokenType) {
			return GeometryNodeToken;
		}
		else if (GeometryObjectType == tokenType) {
			return GeometryObjectToken;
		}
		else if (TransformType == tokenType) {
			return TransformToken;
		}
		else if (MeshType == tokenType) {
			return MeshToken;
		}
		else if (VertexArrayType == tokenType) {
			return VertexArrayToken;
		}
		else if (IndexArrayType == tokenType) {
			return IndexArrayToken;
		}
		else if (MaterialType == tokenType) {
			return MaterialToken;
		}
		else if (ColorType == tokenType) {
			return ColorToken;
		}
		else if (TextureType == tokenType) {
			return TextureToken;
		}

		return NoneType;
	}

} // Namespace Grammar

namespace OGEXParser 
{

	struct OpenGEXParser::DImplementStruct
	{
		DImplementStruct()
			: context(nullptr)
		{

		}

		Context* context;
	};

	OpenGEXParser::OpenGEXParser()
		: dataSummary(nullptr)
	{
		dImpl = new DImplementStruct;
	}

	OpenGEXParser::~OpenGEXParser()
	{
		if (dataSummary)
		{
			delete dataSummary;
		}
		delete dImpl;
	}

	bool OpenGEXParser::parse(const char* buffer, int32 len)
	{
		delete dataSummary;
		dataSummary = nullptr;
		dImpl->context = false;

		if (!buffer)
			return false;

		OpenDDLParser openDDLParser(buffer, len);
		bool result = openDDLParser.parse();
		if (!result)
			return false;

		dImpl->context = openDDLParser.getContext();
		processNodes(openDDLParser.getRoot());

		return true;
	}

	void OpenGEXParser::processNodes(ODDLParser::DDLNode* node)
	{
		if (!node)
			return;
		DDLNode::DllNodeList childNodes = node->getChildNodeList();
		for (DDLNode::DllNodeList::iterator iter = childNodes.begin(); iter != childNodes.end(); ++iter)
		{
			Grammar::TokenType tokenType(Grammar::matchTokenType((*iter)->getType().c_str()));
			switch (tokenType)
			{
			case Grammar::MetricKeyToken:
			{
				processMetricNode(*iter);
			}
			break;
			}
		}
	}

	void OpenGEXParser::processMetricNode(ODDLParser::DDLNode* node)
	{
		if (node == nullptr || dImpl->context == nullptr)
			return;

		if (node->getParent() != dImpl->context->m_root)
			return;

		ODDLParser::Property* prop(node->getProperties());
		while (prop != nullptr)
		{
			if (!prop->m_key)
				continue;

			Text& keyText = *prop->m_key;
			if (keyText == Grammar::Metric_DistanceType)
			{
				if (prop->m_value->m_type == Value::ddl_float)
				{
					dataSummary->distanceScale = prop->m_value->getFloat();
				}
			}
			else if (keyText == Grammar::Metric_AngleType)
			{
				if (prop->m_value->m_type == Value::ddl_float)
				{
					dataSummary->angleScale = prop->m_value->getFloat();
				}
			}
			else if (keyText == Grammar::Metric_TimeType)
			{
				if (prop->m_value->m_type == Value::ddl_float)
				{
					dataSummary->timeScale = prop->m_value->getFloat();
				}
			}
			else if (keyText == Grammar::Metric_UpType)
			{
				if (prop->m_value->m_type == Value::ddl_string)
				{
					std::string upDirStr = prop->m_value->getString();
					int32 upDirV = UAD_Z;
					if (upDirStr == "x")
					{
						upDirStr = UAD_X;
					}
					else if (upDirStr == "y")
					{
						upDirStr = UAD_Y;
					}
					else if (upDirStr == "z")
					{
						upDirStr = UAD_Z;
					}
					dataSummary->upDirection = upDirV;
				}
			}

			prop = prop->m_next;
		}
	}

}
