

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);


cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);
    float3 EmissiveColor            : packoffset(c1);
    float3 SpecularColor            : packoffset(c2);
    float  SpecularPower : packoffset(c2.w);

    float3 LightDirection[3]        : packoffset(c3);
    float3 LightDiffuseColor[3]     : packoffset(c6);
    float3 LightSpecularColor[3]    : packoffset(c9);

    float3 EyePosition              : packoffset(c12);

    float3 FogColor                 : packoffset(c13);
    float4 FogVector                : packoffset(c14);

    float4x4 World                  : packoffset(c15);
    float3x3 WorldInverseTranspose  : packoffset(c19);
    float4x4 WorldViewProj          : packoffset(c22);
};

cbuffer Parameters : register(b1)
{
    float SpotLightPower : packoffset(c0.x);
    float LightPower : packoffset(c0.y);
    float Att2 : packoffset(c0.z);
    float3 SpotLight :  packoffset(c1);
    float3 LightPosition : packoffset(c2);
    float3 LightAmbient : packoffset(c3);
    float3 EyePos : packoffset(c4);
    float Near : packoffset(c5.x);
    float Far : packoffset(c5.y);
};

struct PSInputPixelLightingTx
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 Diffuse      : COLOR0;
};

// Pixel shader: pixel lighting.
float4 main(PSInputPixelLightingTx pin) : SV_TARGET
{
// �����̕���
    float3 lightDirection = pin.PositionWS.xyz - SpotLight;
  
    // �����܂ł̋���
    float lightDistance = length(lightDirection);

    // ��������̋����̉e��
    float atten = saturate(SpotLightPower / (lightDistance * lightDistance));

   // �e�N�X�`���F �~ Vc���w�肳��Ă���ꍇ�͒��_�J���[ + �A���t�@
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;

    // �@���𐳋K��
   float3 worldNormal = normalize(pin.NormalWS);

   // ���̋�������ς���Z�o����
   float3 dotL = dot(LightPosition, worldNormal);

   // �\�ʂ̏ꍇ�͂P�A���ʂ̏ꍇ��0
   float3 zeroL = step(0, dotL);

   // ���ʂ̏ꍇ�͍��ɂȂ�
   float3 diffuse = zeroL * dotL;// ���̋�������ς���Z�o����
 
   float3 dotSpot = dot(SpotLight, worldNormal);

   // �\�ʂ̏ꍇ�͂P�A���ʂ̏ꍇ��0
   float3 zeroSpot = step(0.0f, dotSpot);

   // ���ʂ̏ꍇ�͍��ɂȂ�
   float3 SpotDiffuse = dotSpot * zeroSpot;
   SpotDiffuse *= atten;

   // �}�e���A���̃f�B�t���[�Y�F���|����
   diffuse = diffuse * DiffuseColor.rgb + EmissiveColor;

   // �}�e���A���̃f�B�t���[�Y�F���|����
   SpotDiffuse = SpotDiffuse * DiffuseColor.rgb + EmissiveColor;

   // ���̉e�����|����
   color.rgb *= SpotDiffuse + (diffuse * (1.0f-LightAmbient)) * LightPower + LightAmbient;

    //���_�Ǝ��_�Ƃ̋������v�Z����
   float d = distance( pin.PositionWS.xyz, EyePos.xyz );
    float4 m_FogColor = float4(135.0f / 255.0f, 206.0f / 255.0f, 1, 1); //�t�H�O�J���[

   float f = ( Far - d ) / ( Far - Near );
   f = clamp( f, 0.0f, 1.0f );
   //�I�u�W�F�N�g�̃����o�[�g�g�U�Ɩ��̌v�Z���ʂƃt�H�O�J���[����`��������
    float4 Out = color * f + m_FogColor * (1.0f - f);

   // �����x�N�g��
    float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
 
    // �n�[�t�x�N�g��
    float3 halfVector = normalize(eyeVector - lightDirection);
 
    // �X�y�L�����̉e����������ς��g�����߂�
    float dotH = dot(halfVector, worldNormal);
 
    // �X�y�L�����p���[���w���Ƃ��Ďg���n�C���C�g�̂������𒲐�
    float3 specular = pow(max(dotH, 0) * zeroL, SpecularPower) * dotL;
 
    // ���C�g�̃X�y�L�����F�ƃ}�e���A���̃X�y�L�����F�𔽉f
    specular = specular * LightSpecularColor[0] * SpecularColor;
 
    // �X�y�L������������
    color.rgb += specular * color.a;
 //  discard;
    
    float uvx = pin.PositionWS.y;
        //���肩�肩��ύX��
    float max = 300.0f;

    if (uvx <= max)
    {
        uvx /= max;
        float wari = uvx;
        uvx = 1 - uvx;
        uvx *= 3;
    
        float4 col = float4(uvx, uvx, uvx, 1);

        return lerp(col, color * float4(2.1f, 1.4f, 0.7f, 1), wari);
    }
    return color * float4(2.1f, 1.4f, 0.7f, 1);
}
