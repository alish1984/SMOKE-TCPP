/*-----------------------------------------------------------------------*\
|                  _       _____ __  __  ____  _  ________                |
|                 | |     / ____|  \/  |/ __ \| |/ /  ____|               |
|          ___  __| | ___| (___ | \  / | |  | | ' /| |__                  |
|         / _ \/ _` |/ __|\___ \| |\/| | |  | |  < |  __|                 |
|        |  __/ (_| | (__ ____) | |  | | |__| | . \| |____                |
|         \___|\__,_|\___|_____/|_|  |_|\____/|_|\_\______|               |
|                                                                         |
|                                                                         |
|   Authors: A. Cuoci, M.R. Malik, Z. Li, A. Parente                      |
|                                                                         |
|   Contacts: Alberto Cuoci                                               |
|   email: alberto.cuoci@polimi.it                                        |
|   Department of Chemistry, Materials and Chemical Engineering           |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano (Italy)                      |
|                                                                         |
|   Contacts: Mohammad Rafi Malik, Zhiyi Li, Alessandro Parente           |
|   Aero-Thermo-Mechanical Department                                     |
|   Université Libre de Bruxelles                                         |
|   Avenue F. D. Roosevelt 50, 1050 Bruxelles (Belgium)                   |
|                                                                         |
|-------------------------------------------------------------------------|
|                                                                         |
|   This file is part of edcSMOKE solver.                                 |
|                                                                         |
|	License                                                           |
|                                                                         |
|   Copyright(C) 2017-2014 A. Cuoci, A. Parente                           |
|   edcSMOKE is free software: you can redistribute it and/or modify      |
|   it under the terms of the GNU General Public License as published by  |
|   the Free Software Foundation, either version 3 of the License, or     |
|   (at your option) any later version.                                   |
|                                                                         |
|   edcSMOKE is distributed in the hope that it will be useful,           |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of        |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
|   GNU General Public License for more details.                          |
|                                                                         |
|   You should have received a copy of the GNU General Public License     |
|   along with edcSMOKE. If not, see <http://www.gnu.org/licenses/>.      |
|                                                                         |
\*-----------------------------------------------------------------------*/
	Info<< "PSR calculations for time 0.0055" <<endl;
	int filterWidth=12;
	const int n = 864*1008*576/(pow(filterWidth,3));//mesh size for LES with filterwidth 12 compared to H case DNS
	const int n0 =0;
	const int n1 =0;
	const int n2 =n;//100e6;
	scalar volume_cell = ((1.37*0.001)/72)*((1.37*0.001)/72)*((1.37*0.001)/72)*pow(filterWidth,3);//cell volume size 
	scalarField T_LES_OF(n2,0.0);
	Info<<"T_LES made"<<endl;
	scalarField rho_LES_OF(n2,0.0);
	Info<<"rho_LES made"<<endl;
	scalarField p_LES_OF(n2,0.0);
	Info<<"p_LES made"<<endl;
	
	scalarField eps_SGS_LES_OF(n2,0.0);
	Info<<"eps_SGS_LES made"<<endl;
	scalarField k_SGS_LES_OF(n2,0.0);
	Info<<"k_SGS_LES made"<<endl;
	scalarField nu_LES_OF(n2,0.0);
	Info<<"nu_LES made"<<endl;
	
	scalarField ReTau_LES(n2,0.0);
	Info<<"ReTau_LES made"<<endl;
	scalarField gammaL_LES(n2,0.0);
	Info<<"gammaL_LES made"<<endl;
	scalarField tauStar_LES(n2,0.0);
	Info<<"tauStar_LES made"<<endl;
	scalarField gammaStar_LES(n2,0.0);
	Info<<"gammaStar_LES made"<<endl;
	scalarField mDotStar_LES(n2,0.0);
	Info<<"mDotStar_LES made"<<endl;
	scalarField tfStar_LES(n2,0.0);
	Info<<"tfStar_LES made"<<endl;		
	List<List<scalar> > YStar_LES(11, List<scalar>(n2) ); 
	Info<<"YStar_LES made"<<endl;
		scalarField TStar_LES(n2,0.0);
	Info<<"TStar_LES made"<<endl;
		scalarField edc_coefficient_LES(n2,0.0);
	Info<<"edc_coefficient_LES made"<<endl;
		scalarField edc_coefficient_PFR_tfFlow_LES(n2,0.0);
	Info<<"edc_coefficient_PFR_tfFlow_LES made"<<endl;
	
	List<List<scalar> > tauChemSpecie_LES(11, List<scalar>(n2) );
	Info<<"tauChemSpecie_LES made"<<endl;
	
	

	List<List<scalar> > Y_LES(11, List<scalar>(n2) ); 
	Info<<"Y_LES_LES made"<<endl;
	List<List<scalar> > R_LES(11, List<scalar>(n2) );
	Info<<"R_LES_LES made"<<endl;
	//scalarField T_LES_Final(n2,0.0);
	scalarField QdotCells_LES(n2,0.0);
	scalarField dQCells_LES(n2,0.0);
	
	{

	
		float* nu_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_nu_0055.dat",n);
		Info<<nu_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) nu_LES_OF[celli]=nu_LES[celli+n1];
		delete nu_LES;nu_LES=NULL;
		
	
		float* eps_SGS_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_eSGS_0055.dat",n);
		Info<<eps_SGS_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) eps_SGS_LES_OF[celli]=eps_SGS_LES[celli+n1];
		delete eps_SGS_LES;eps_SGS_LES=NULL;
		
		
		float* k_SGS_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_residualKineticEnergy_0055.dat",n);
		Info<<k_SGS_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) k_SGS_LES_OF[celli]=k_SGS_LES[celli+n1];
		delete k_SGS_LES;k_SGS_LES=NULL;
		
		float* T_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_T_0055.dat",n);
		Info<<T_LES[10]<<endl;

		for(int celli=n0;celli<n2;celli++) T_LES_OF[celli]=T_LES[celli+n1];
		delete T_LES;T_LES=NULL;
	
		float* rho_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_rho_0055.dat",n);
		Info<<rho_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) rho_LES_OF[celli]=rho_LES[celli+n1];
		delete rho_LES;rho_LES=NULL;
	
		float* p_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_P_0055.dat",n);
		Info<<p_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) p_LES_OF[celli]=p_LES[celli+n1];
		delete p_LES;p_LES=NULL;
	
		float* Y_CO2_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_CO2_0055.dat",n);
		Info<<Y_CO2_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[8][celli]=Y_CO2_LES[celli+n1];
		delete Y_CO2_LES;Y_CO2_LES=NULL; 
		
		float* Y_CO_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_CO_0055.dat",n);
		Info<<Y_CO_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[7][celli]=Y_CO_LES[celli+n1];
		delete Y_CO_LES;Y_CO_LES=NULL;
		
		float* Y_H_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_H_0055.dat",n);
		Info<<Y_H_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[5][celli]=Y_H_LES[celli+n1];
		delete Y_H_LES;Y_H_LES=NULL;
	
		float* Y_H2_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_H2_0055.dat",n);
		Info<<Y_H2_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[0][celli]=Y_H2_LES[celli+n1];
		delete Y_H2_LES;Y_H2_LES=NULL;
	
		float* Y_H2O_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_H2O_0055.dat",n);	
		Info<<Y_H2O_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[4][celli]=Y_H2O_LES[celli+n1];
		delete Y_H2O_LES;Y_H2O_LES=NULL;
	
		float* Y_HCO_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_HCO_0055.dat",n);
		Info<<Y_HCO_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[9][celli]=Y_HCO_LES[celli+n1];
		delete Y_HCO_LES;Y_HCO_LES=NULL;
	
		float* Y_HO2_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_HO2_0055.dat",n);
		Info<<Y_HO2_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[6][celli]=Y_HO2_LES[celli+n1];
		delete Y_HO2_LES;Y_HO2_LES=NULL;
	
		float* Y_O_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_O_0055.dat",n);
		Info<<Y_O_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[2][celli]=Y_O_LES[celli+n1];
		delete Y_O_LES;Y_O_LES=NULL;
	
		float* Y_O2_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_O2_0055.dat",n);
		Info<<Y_O2_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[1][celli]=Y_O2_LES[celli+n1];
		delete Y_O2_LES;Y_O2_LES=NULL;
	
		float* Y_OH_LES=readFloatBinaryFile("/scratch/Ali/Filtered_Interpolated_RAW_DNS_HAWKES_DATA_le/HIGH/jet_0055/jet_Filtered12_Y_OH_0055.dat",n);	
		Info<<Y_OH_LES[10]<<endl;
		for(int celli=n0;celli<n2;celli++) Y_LES[3][celli]=Y_OH_LES[celli+n1];
		delete Y_OH_LES;Y_OH_LES=NULL;
	
		for(int celli=n0;celli<n2;celli++)
		{
			scalar sum=0.0;
			for(int i=0;i<10;i++)
			{
				sum+=Y_LES[i][celli];
			}
			Y_LES[10][celli]=1.0-sum;
		}

	}
	
	unsigned int counter = 0;
	const int unsigned ns = thermodynamicsMapXML->NumberOfSpecies();
	scalar numberOfResidenceTimes = 100.;
		
	OpenSMOKE::OpenSMOKEVectorDouble omegaMean(ns);
	OpenSMOKE::OpenSMOKEVectorDouble omegaStar(ns);
	OpenSMOKE::OpenSMOKEVectorDouble xMean(ns);
	OpenSMOKE::OpenSMOKEVectorDouble cMean(ns);
	OpenSMOKE::OpenSMOKEVectorDouble h_species(ns);
	OpenSMOKE::OpenSMOKEVectorDouble xStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble cStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble RStar_(ns);
	OpenSMOKE::OpenSMOKEVectorDouble rStar_(ns);
	
	Eigen::VectorXd yStar0(ns+3);
	Eigen::VectorXd yStarf(ns+3);
		

		
	double hMean, MWMean;
	const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
	double tfFlow_LES = 2e-09*pow(filterWidth,3);;
	#include "edc.H"
	for(int celli=n0;celli<n2;celli++)
	{
		// Integration time
		const double t0 = 0.;
		double tf = 0.;
			
		const double tStart = OpenSMOKE::OpenSMOKEGetCpuTime();
		//fine_structure_ode_pfr.Set(p_DNS_OF[celli]);//fine_structure_ode_pfr.Set(pCells[celli]);
		
		for(unsigned int i=0;i<ns;i++)
				yStar0(i) = Y_LES[i][celli];
		yStar0(ns) = T_LES_OF[celli];
		yStar0(ns+1) = 0.;
		yStar0(ns+2) = 0.;
		
		for(unsigned int i=0;i<ns;i++)
				omegaMean[i+1] =Y_LES[i][celli];
				
		// Extract the star mass fractions
		for(unsigned int i=1;i<=ns;i++)
				omegaStar[i] = omegaMean[i];

		
		// Convert to mole fractions
		thermodynamicsMapXML->MoleFractions_From_MassFractions(xMean.GetHandle(), MWMean, omegaMean.GetHandle());

		// Initialize the fine structure
		thermodynamicsMapXML->SetTemperature(T_LES_OF[celli]);
		thermodynamicsMapXML->SetPressure(p_LES_OF[celli]);
		hMean = thermodynamicsMapXML->hMolar_Mixture_From_MoleFractions(xMean.GetHandle());
		hMean/=MWMean;	
		
		fine_structure_ode_psr.Set(T_LES_OF[celli], p_LES_OF[celli], omegaMean, omegaStar, hMean, gammaStar_LES[celli], mDotStar_LES[celli]);

		tf = numberOfResidenceTimes/max(mDotStar_LES[celli], SMALL);
		//tf = 1./max(mDotStar_LES[celli], SMALL);
		//double reserve=tf;
		//tf=reserve*reserve*reserve;
		
		#include "solvePSR_DI.H"
		
		for(unsigned int i=0;i<ns;i++)
				YStar_LES[i][celli] = yStarf(i);
		TStar_LES[celli] = yStarf(ns);
				 
		for(unsigned int i=0;i<ns;i++)
			R_LES[i][celli]  = rho_LES_OF[celli]*edc_coefficient_LES[celli]*(YStar_LES[i][celli]-Y_LES[i][celli]);

		if (counter%(int(0.001*n2)+1) == 0)
		{
			Info << "   Accomplished: " << counter << "/" << n2<< endl;
		}
		counter++;
	}
	
	scalarField tmp_R_i_LES(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[0][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_H2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[1][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_O2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[2][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[3][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_OH_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[4][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_H2O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[5][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_H_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[6][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_HO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[7][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_CO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[8][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_CO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[9][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_HCO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_R_i_LES[celli]=R_LES[10][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_RR_N2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_R_i_LES);
	
	scalarField tmp_Y_i_LES(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=YStar_LES[0][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_H2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[1][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_O2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[2][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[3][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_OH_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[4][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_H2O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[5][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_H_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[6][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_HO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[7][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_CO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[8][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_CO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[9][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_HCO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_Y_i_LES[celli]=Y_LES[10][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_YStar_LES_N2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_Y_i_LES);
	
	scalarField tmp_tauChemSpecie_i_LES(n2,0.0);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[0][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_H2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[1][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_O2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[2][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[3][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_OH_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[4][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_H2O_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[5][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_H_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[6][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_HO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[7][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_CO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[8][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_CO2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[9][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_HCO_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	for(int celli=n0;celli<n2;celli++) tmp_tauChemSpecie_i_LES[celli]=tauChemSpecie_LES[10][celli];
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauChemSpecie_N2_0055_edc_PSR_orig_limitedGammaL.dat",n2,tmp_tauChemSpecie_i_LES);
	
	//writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_QdotCells_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,QdotCells_LES);
	//writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_dQCells_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,dQCells_LES);
	
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_ReTau_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,ReTau_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_gammaL_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,gammaL_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tauStar_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,tauStar_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_gammaStar_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,gammaStar_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_mDotStar_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,mDotStar_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_tfStar_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,tfStar_LES);
	writedoubleBinaryFile("/scratch/Ali/A-Priori-LES-Data/HIGH/jet_0055/filterWidth12/jet_TStar_LES_0055_edc_PSR_orig_limitedGammaL.dat",n2,TStar_LES);

	const double tEnd = OpenSMOKE::OpenSMOKEGetCpuTime();		
	Info << "CPU time for chemistry (EDC): " << tEnd - tStart << " s " << endl;		
