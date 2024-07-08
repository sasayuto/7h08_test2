#include "SM_Common.hlsli"

Texture2D<float4> Texture : register(t0);
// �V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture[MAX_CASCADE] : register(t3);
// �V���h�E�}�b�v�e�N�X�`��
Texture2D MoveShadowMapTexture[MAX_CASCADE] : register(t7);
sampler Sampler : register(s0);

// �V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState ShadowMapSampler : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS[MAX_CASCADE] : TEXCOORD3;
    float4 MoveLightPosPS[MAX_CASCADE] : TEXCOORD7;
};

// �}�b�n�o���h�΍�
#define SHADOW_EPSILON 0.0004f

float4 main(Input pin) : SV_TARGET0
{
    // ���C�g�̌��������߂�
    float lightlength = length(pin.PositionWS.xyz);
    float4 diffuse;
    float3 specular = 0;
    float percentLit = 1;
    float cascadeNum = -1;

            //�ǂ̃��C�g�����񂠂����Ă邩���ׂ�
    for (int i = 0; i < MAX_CASCADE; i++)
        {
        //���C�g�܂ł̕���
            float targetLength = length(pin.PositionWS.xyz - StaticTargetPosition);
             // ------------------------------------------------------------------------------- //
            //�V���h�E�}�b�v�̉e�̌v�Z
            // ------------------------------------------------------------------------------- //
            // ���K���f�o�C�X���W�ɂ���
                    //�͈͓���
            if (targetLength < Lightdistance[i].w)
            {

            float4 lightPosPS = pin.LightPosPS[i];
            lightPosPS.xyz /= lightPosPS.w;

            // �Q�Ƃ���V���h�E�}�b�v��UV�l�����߂�
            float2 uv = lightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;
            
            percentLit *= (ShadowMapTexture[i].SampleCmpLevelZero(ShadowMapSampler, uv, lightPosPS.z - SHADOW_EPSILON).x);
              break;
            }
        }
                //�ǂ̃��C�g�����񂠂����Ă邩���ׂ�
      for (int x = 0; x < MAX_CASCADE; x++)
        {
         //���C�g�܂ł̕���
            float targetLength = length(pin.PositionWS.xyz - DynamicTargetPosition);
             // ------------------------------------------------------------------------------- //
            //�V���h�E�}�b�v�̉e�̌v�Z
            // ------------------------------------------------------------------------------- //
            // ���K���f�o�C�X���W�ɂ���
                    //�͈͓���
            if (targetLength < Lightdistance[x].w)
            {
                pin.MoveLightPosPS[x].xyz /= pin.MoveLightPosPS[x].w;

            // �Q�Ƃ���V���h�E�}�b�v��UV�l�����߂�
                float2 moveUV = pin.MoveLightPosPS[x].xy * float2(0.5f, -0.5f) + 0.5f;

                percentLit *= (MoveShadowMapTexture[x].SampleCmpLevelZero(ShadowMapSampler, moveUV, pin.MoveLightPosPS[x].z - SHADOW_EPSILON).x);
                cascadeNum = x;
                break;
            }
        }
    // ------------------------------------------------------------------------------- //
    // �f�B�t���[�Y
    // ------------------------------------------------------------------------------- //
        //    //cascade�̈ʒu�̐F
        //float cascadeShadow[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        //float3 shadowColor = 1;
        //if (cascadeNum != -1)
        //{
    
        //    for (int i = 0; i < 4; i++)
        //        if (cascadeNum == i)
        //            cascadeShadow[i] += 1;
        //    shadowColor = float3(cascadeShadow[0] + cascadeShadow[3] * 2, cascadeShadow[1], cascadeShadow[2]);
        //}


    // �@���𐳋K��
        float3 worldNormal = normalize(pin.NormalWS);

    // ���̋�������ς���Z�o����
    float3 dotL = saturate(dot(-LightDir, worldNormal));

    // ���C�g�ɂ�閾�邳�����߂�
    float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;

    // �f�B�t���[�Y�F�����߂� 
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

    // ------------------------------------------------------------------------------- //
    // �X�y�L����
    // ------------------------------------------------------------------------------- //
    
         // �����x�N�g��
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);

        // �n�[�t�x�N�g��
        float3 halfVector = normalize(eyeVector - LightDir);

        // �X�y�L�����̉e����������ς��g�����߂�
        float dotH = saturate(dot(halfVector, worldNormal));

        // �X�y�L�����p���[���w���Ƃ��Ďg���n�C���C�g�̂������𒲐�
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    // ------------------------------------------------------------------------------- //
    
        // �e�N�X�`���F���|���� 
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;

    float4 m_FogColor = float4(1,1, 1, 1); //�t�H�O�J���[

//���_�Ǝ��_�Ƃ̋������v�Z����
    float d = distance(pin.PositionWS.xyz, EyePosition);

    float f = (Far - d) / (Far - Near);
    f = clamp(f, 0.0f, 1.0f);
    
   //�I�u�W�F�N�g�̃����o�[�g�g�U�Ɩ��̌v�Z���ʂƃt�H�O�J���[����`��������
    float4 Out = color * f * float4(3,2,1,1) + m_FogColor * (1.0f - f);

      // �X�y�L������������
    Out.rgb += specular * diffuse.a;

    return Out;
}


