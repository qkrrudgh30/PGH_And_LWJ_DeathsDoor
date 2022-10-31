Shader "Custom/BlendTexturesCartoon" {
	Properties {
		_Color ("Tint All", Vector) = (1,1,1,1)
		_Tint1 ("Texture 1 Tint", Vector) = (1,1,1,1)
		_Tint2 ("Texture 2 Tint", Vector) = (1,1,1,1)
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_MainTex2 ("Albedo2 (RGB)", 2D) = "white" {}
		_Blend ("Blend (RGB)", 2D) = "white" {}
		_Threshold ("blend threshold", Range(0, 1)) = 0
		_Threshold_Out ("Outer Threshold", Range(0, 1)) = 0
		_Threshold_In ("Inner Threshold", Range(0, 1)) = 0
		_EdgeThreshold ("Edge Threshold", Range(0, 1)) = 0
		_EdgeColor ("Edge Color", Vector) = (0,0,0,1)
	}
	//DummyShaderTextExporter
	SubShader{
		Tags { "RenderType"="Opaque" }
		LOD 200
		CGPROGRAM
#pragma surface surf Standard
#pragma target 3.0

		sampler2D _MainTex;
		fixed4 _Color;
		struct Input
		{
			float2 uv_MainTex;
		};
		
		void surf(Input IN, inout SurfaceOutputStandard o)
		{
			fixed4 c = tex2D(_MainTex, IN.uv_MainTex) * _Color;
			o.Albedo = c.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	Fallback "Diffuse"
}